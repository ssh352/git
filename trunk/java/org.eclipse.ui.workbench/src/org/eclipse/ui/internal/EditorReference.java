/*******************************************************************************
 * Copyright (c) 2006, 2010 IBM Corporation and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *     IBM Corporation - initial API and implementation
 *     Nikolay Botev - bug 240651
 *******************************************************************************/
package org.eclipse.ui.internal;

import org.eclipse.ui.internal.testing.ContributionInfoMessages;

import org.eclipse.core.runtime.IAdaptable;
import org.eclipse.core.runtime.IPath;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Path;
import org.eclipse.jface.preference.IPreferenceStore;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.osgi.util.NLS;
import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.IEditorPart;
import org.eclipse.ui.IEditorReference;
import org.eclipse.ui.IEditorRegistry;
import org.eclipse.ui.IElementFactory;
import org.eclipse.ui.IMemento;
import org.eclipse.ui.IPersistableEditor;
import org.eclipse.ui.IPersistableElement;
import org.eclipse.ui.IReusableEditor;
import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.IWorkbenchPart;
import org.eclipse.ui.IWorkbenchPart2;
import org.eclipse.ui.IWorkbenchPart3;
import org.eclipse.ui.IWorkbenchPartConstants;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.internal.editorsupport.ComponentSupport;
import org.eclipse.ui.internal.misc.StatusUtil;
import org.eclipse.ui.internal.misc.UIStats;
import org.eclipse.ui.internal.part.NullEditorInput;
import org.eclipse.ui.internal.registry.EditorDescriptor;
import org.eclipse.ui.internal.registry.EditorRegistry;
import org.eclipse.ui.internal.tweaklets.TabBehaviour;
import org.eclipse.ui.internal.tweaklets.Tweaklets;
import org.eclipse.ui.internal.util.Util;
import org.eclipse.ui.part.AbstractMultiEditor;
import org.eclipse.ui.part.IWorkbenchPartOrientation;
import org.eclipse.ui.part.MultiEditor;
import org.eclipse.ui.part.MultiEditorInput;
import org.eclipse.ui.statushandlers.StatusManager;
import org.eclipse.ui.testing.ContributionInfo;

public class EditorReference extends WorkbenchPartReference implements
        IEditorReference {

    /**
     * 
     */
    private final EditorManager manager;

    private IMemento editorMemento;

	private IMemento editorState = null;

    /**
     * Flag that lets us detect malfunctioning editors that don't fire PROP_INPUT events.
     * It is never needed for a correctly-functioning
     */
    private boolean expectingInputChange = false;
    
    /**
     * Flag that determines whether we've already reported that this editor is malfunctioning.
     * This prevents us from spamming the event log if we repeatedly detect the same error in
     * a particular editor. If we ever detect an editor is violating its public contract in
     * a way we can recover from (such as a missing property change event), we report the error
     * once and then silently ignore errors from the same editor.
     */
    private boolean reportedMalfunctioningEditor = false;
    
    /**
     * User-readable name of the editor's input
     */
    String name;

    String factoryId;

    IEditorInput restoredInput;
    
	/**
	 * If the reference is instantiated as a AbstractMultiEditor, we need to dispose the
	 * inner references correctly.
	 */
	private IEditorReference[] multiEditorChildren = null;

    
    /**
	 * @param manager
	 *            The editor manager for this reference
	 * @param input
	 *            our input
	 * @param desc
	 *            the descriptor from the declaration
	 */
	public EditorReference(EditorManager manager, IEditorInput input,
			EditorDescriptor desc) {
		this(manager, input, desc, null);
	}
    
    /**
	 * @param manager
	 *            The editor manager for this reference
	 * @param input
	 *            our input
	 * @param desc
	 *            the descriptor from the declaration
	 * @param editorState
	 *            propagate state from another editor. Can be <code>null</code>.
	 */
	public EditorReference(EditorManager manager, IEditorInput input,
			EditorDescriptor desc, IMemento editorState) {
		this.manager = manager;
		initListenersAndHandlers();
		restoredInput = input;
		this.editorState = editorState;
		
		String title = null;
		if (input != null)
			name = title = input.getName();
		if (title == null)
			title = desc.getLabel();
		
		String toolTip = null;
		if (input != null)
			toolTip = input.getToolTipText();
		if (toolTip == null)
			toolTip = ""; //$NON-NLS-1$
		
		if (input != null) {
			IPersistableElement persistable = input.getPersistable();
			if (persistable != null)
				factoryId = persistable.getFactoryId();
		}

		init(desc.getId(), title, toolTip, desc.getImageDescriptor(), title, ""); //$NON-NLS-1$
	}
    
    /**
	 * Constructs a new editor reference for use by editors being restored from
	 * a memento.
	 */
    EditorReference(EditorManager manager, IMemento memento) {
        this.manager = manager;
        initListenersAndHandlers();
        this.editorMemento = memento;
        if (EditorManager.useIPersistableEditor()) {
        	editorState = editorMemento.getChild(IWorkbenchConstants.TAG_EDITOR_STATE);
        } else {
        	editorState = null;
        }
        String id = memento.getString(IWorkbenchConstants.TAG_ID);
        String title = memento.getString(IWorkbenchConstants.TAG_TITLE);
        String tooltip = Util.safeString(memento
                .getString(IWorkbenchConstants.TAG_TOOLTIP));
        String partName = memento
                .getString(IWorkbenchConstants.TAG_PART_NAME);

        IMemento propBag = memento.getChild(IWorkbenchConstants.TAG_PROPERTIES);
		if (propBag != null) {
			IMemento[] props = propBag
					.getChildren(IWorkbenchConstants.TAG_PROPERTY);
			for (int i = 0; i < props.length; i++) {
				propertyCache.put(props[i].getID(), props[i].getTextData());
			}
		}

		// For compatibility set the part name to the title if not found
        if (partName == null) {
            partName = title;
        }

        // Get the editor descriptor.
        EditorDescriptor desc = null;
        if (id != null) {
            desc = getDescriptor(id);
        }
        // desc may be null if id is null or desc is not found, but findImage below handles this
        String location = memento.getString(IWorkbenchConstants.TAG_PATH);
        IPath path = location == null ? null : new Path(location);
        ImageDescriptor iDesc = this.manager.findImage(desc, path);

        this.name = memento.getString(IWorkbenchConstants.TAG_NAME);
        if (this.name == null) {
            this.name = title;
        }
        setPinned("true".equals(memento.getString(IWorkbenchConstants.TAG_PINNED))); //$NON-NLS-1$

        IMemento inputMem = memento.getChild(IWorkbenchConstants.TAG_INPUT);
        if (inputMem != null) {
            this.factoryId = inputMem
                    .getString(IWorkbenchConstants.TAG_FACTORY_ID);
        }

        init(id, title, tooltip, iDesc, partName, ""); //$NON-NLS-1$
    }

    public EditorDescriptor getDescriptor() {
        return getDescriptor(getId());
    }
    
    /**
     * @since 3.1
     *
     * @param id the id
     * @return the editor descriptor
     */
    private EditorDescriptor getDescriptor(String id) {
        EditorDescriptor desc;
        IEditorRegistry reg = WorkbenchPlugin.getDefault()
                .getEditorRegistry();
        desc = (EditorDescriptor) reg.findEditor(id);
        return desc;
    }
    
    /**
     * Initializes the necessary editor listeners and handlers
     */
    private void initListenersAndHandlers() {
        // Create a property change listener to track the "close editors automatically"
        // preference and show/remove the pin icon on editors
        // Only 1 listener will be created in the EditorManager when necessary
        this.manager.checkCreateEditorPropListener();
        // Create a keyboard shortcut handler for pinning editors
        // Only 1 handler will be created in the EditorManager when necessary
        this.manager.checkCreatePinEditorShortcutKeyHandler();
    }

    protected PartPane createPane() {
        return new EditorPane(this, this.manager.page, this.manager.editorPresentation.getActiveWorkbook());
    }
    
    /**
     * This method is called when there should be a change in the editor pin
     * status (added or removed) so that it will ask its presentable part
     * to fire a PROP_TITLE event in order for the presentation to request
     * the new icon for this editor
     */
    public void pinStatusUpdated() {
        firePropertyChange(IWorkbenchPart.PROP_TITLE);
    }
    
    public String getFactoryId() {
        IEditorPart editor = getEditor(false);
        if (editor != null) {
            IPersistableElement persistable = editor.getEditorInput()
                    .getPersistable();
            if (persistable != null) {
				return persistable.getFactoryId();
			}
            return null;
        }
        return factoryId;
    }

    protected String computePartName() {
        if (part instanceof IWorkbenchPart2) {
            return super.computePartName();
        }
		return getRawTitle();
    }

    public String getName() {
        if (part != null) {
			return getEditor(false).getEditorInput().getName();
		}
        return name;
    }

	public String internalGetName() {
		return name;
	}

    public IEditorPart getEditor(boolean restore) {
        return (IEditorPart)getPart(restore);
    }

    protected void releaseReferences() {
        super.releaseReferences();
        editorMemento = null;
        editorState = null;
        name = null;
        factoryId = null;
        restoredInput = null;
    }

    void setName(String name) {
        this.name = name;
    }

    public IMemento getMemento() {
        return editorMemento;
    }

    public IWorkbenchPage getPage() {
        return this.manager.page;
    }

    protected void doDisposeNestedParts() {
		// MultiEditor backwards compatibility
    	if (part instanceof AbstractMultiEditor && !(part instanceof MultiEditor)) {
    		disposeMultiEditorChildren();
    	}
	}

	protected void doDisposePart() {
		// MultiEditor backwards compatibility
		if (part instanceof MultiEditor) {
			disposeMultiEditorChildren();
		}
		
    	IEditorPart editor = (IEditorPart) part;
        super.doDisposePart();
    	if (editor != null) {
            EditorSite site = (EditorSite) editor.getEditorSite();
            manager.disposeEditorActionBars((EditorActionBars) site.getActionBars());
            site.dispose();
        }
        
        this.manager.checkDeleteEditorResources();

        editorMemento = null;
        editorState = null;
        restoredInput = new NullEditorInput();
    }

	private void disposeMultiEditorChildren() {
		if (multiEditorChildren!=null) {
			for (int i=0; i<multiEditorChildren.length; ++i) {
				EditorReference ref = (EditorReference)multiEditorChildren[i];
				if (ref!=null) {
					ref.dispose();
				}
			}
			multiEditorChildren = null;
		}
	}

    public IEditorInput getEditorInput() throws PartInitException {
        if (isDisposed()) {
            if (!(restoredInput instanceof NullEditorInput)) {
                restoredInput = new NullEditorInput();
            }
            return restoredInput;
        }
        
        IEditorPart part = getEditor(false);
        if (part != null) {
            return part.getEditorInput();
        }
        return getRestoredInput();
    }
    
    private IEditorInput getRestoredInput() throws PartInitException {
        if (restoredInput != null) {
            return restoredInput;
        }
        
        // Get the input factory.
        IMemento editorMem = getMemento();
        if (editorMem == null) {
            throw new PartInitException(NLS.bind(WorkbenchMessages.EditorManager_no_persisted_state, getId(), getName()));
        }
        IMemento inputMem = editorMem
                .getChild(IWorkbenchConstants.TAG_INPUT);
        String factoryID = null;
        if (inputMem != null) {
            factoryID = inputMem
                    .getString(IWorkbenchConstants.TAG_FACTORY_ID);
        }
        if (factoryID == null) {
            throw new PartInitException(NLS.bind(WorkbenchMessages.EditorManager_no_input_factory_ID, getId(), getName()));
        }
        IAdaptable input = null;
        String label = null; // debugging only
        if (UIStats.isDebugging(UIStats.CREATE_PART_INPUT)) {
            label = getName() != null ? getName() : factoryID;
        }
        try {
            UIStats.start(UIStats.CREATE_PART_INPUT, label);
            IElementFactory factory = PlatformUI.getWorkbench()
                    .getElementFactory(factoryID);
            if (factory == null) {
                throw new PartInitException(NLS.bind(WorkbenchMessages.EditorManager_bad_element_factory, new Object[] { factoryID, getId(), getName() }));
            }

            // Get the input element.
            input = factory.createElement(inputMem);
            if (input == null) {
                throw new PartInitException(NLS.bind(WorkbenchMessages.EditorManager_create_element_returned_null, new Object[] { factoryID, getId(), getName() }));
            }
        } finally {
            UIStats.end(UIStats.CREATE_PART_INPUT, input, label);
        }
        if (!(input instanceof IEditorInput)) {
            throw new PartInitException(NLS.bind(WorkbenchMessages.EditorManager_wrong_createElement_result, new Object[] { factoryID, getId(), getName() }));
        }
        restoredInput = (IEditorInput) input;
        return restoredInput;
    }

    /* (non-Javadoc)
     * @see org.eclipse.ui.IWorkbenchPartReference#getTitleImage()
     * This method will append a pin to the icon of the editor
     * if the "automatically close editors" option in the
     * preferences is enabled and the editor has been pinned.
     */
    public ImageDescriptor computeImageDescriptor() {
        ImageDescriptor descriptor = super.computeImageDescriptor();
        if (!isPinned()) {
			return descriptor;
		}

        // Check if the pinned preference is set
        IPreferenceStore prefStore = WorkbenchPlugin.getDefault()
                .getPreferenceStore();
        boolean bUsePin = prefStore
				.getBoolean(IPreferenceConstants.REUSE_EDITORS_BOOLEAN)
				|| ((TabBehaviour)Tweaklets.get(TabBehaviour.KEY)).alwaysShowPinAction();

        if (!bUsePin) {
			return descriptor;
		}

        ImageDescriptor pinDesc = this.manager.getEditorPinImageDesc();
        if (pinDesc == null) {
			return descriptor;
		}

        return new OverlayIcon(descriptor, pinDesc, new Point(16, 16));
    }

    /**
     * Wrapper for restoring the editor. First, this delegates to busyRestoreEditorHelper
     * to do the real work of restoring the view. If unable to restore the editor, this
     * method tries to substitute an error part and return success.
     *
     * @return the created part
     */
    protected IWorkbenchPart createPart() {
        if (EditorRegistry.EMPTY_EDITOR_ID.equals(getId())) {
        	return getEmptyEditor(getDescriptor());
        }
        PartInitException exception = null;
        
        IWorkbenchPart result = null;
        
        // Try to restore the editor -- this does the real work of restoring the editor
        //
        try {
            result = createPartHelper();
        } catch (PartInitException e) {
            exception = e;
        }

        
        // If unable to create the part, create an error part instead
        // and pass the error to the status handling facility
        if (exception != null) {           
            IStatus originalStatus = exception.getStatus();
            IStatus logStatus = StatusUtil.newStatus(originalStatus,
                    NLS.bind("Unable to create editor ID {0}: {1}",  //$NON-NLS-1$
                            getId(), originalStatus.getMessage()));
            IStatus displayStatus = StatusUtil.newStatus(originalStatus,
            		NLS.bind(WorkbenchMessages.EditorManager_unableToCreateEditor,
            				originalStatus.getMessage()));

			// Pass the error to the status handling facility
            StatusManager.getManager().handle(logStatus);
            
            EditorDescriptor descr = getDescriptor();
            return getEmptyEditor(descr, displayStatus);
        }
        
        return result;
    }
    
    protected void partPropertyChanged(Object source, int propId) {
        
        // Detect badly behaved editors that don't fire PROP_INPUT events
        // when they're supposed to. This branch is only needed to handle
        // malfunctioning editors.
        if (propId == IWorkbenchPartConstants.PROP_INPUT) {
            expectingInputChange = false;
        }
        
        super.partPropertyChanged(source, propId);
    }
    
    /**
     * Attempts to set the input of the editor to the given input. Note that the input
     * can't always be changed for an editor. Editors that don't implement IReusableEditor
     * can't have their input changed once they've been materialized.
     * 
     * @since 3.1
     *
     * @param input new input
     * @return true iff the input was actually changed
     */
    public boolean setInput(IEditorInput input) {

        if (part != null) {
            if (part instanceof IReusableEditor) {
                IReusableEditor editor = (IReusableEditor) part;
       
                expectingInputChange = true;
                
                editor.setInput(input);
                
                // If the editor never fired a PROP_INPUT event, log the fact that we've discovered
                // a buggy editor and fire the event for free. Firing the event for free isn't required
                // and cannot be relied on (it only works if the input change was triggered by this
                // method, and there are definitely other cases where events will still be lost),
                // but older versions of the workbench did this so we fire it here in the spirit
                // of playing nice.
                if (expectingInputChange) {

                    // Log the fact that this editor is broken
                    reportMalfunction("Editor is not firing a PROP_INPUT event in response to IReusableEditor.setInput(...)"); //$NON-NLS-1$
                    
                    // Fire the property for free (can't be relied on since there are other ways the input
                    // can change, but we do it here to be consistent with older versions of the workbench)
                    firePropertyChange(IWorkbenchPartConstants.PROP_INPUT);
                }
                
                return editor.getEditorInput() == input;

            }
            // Can't change the input if the editor already exists and isn't an IReusableEditor
            return false;
        }
        
        // Changing the input is trivial and always succeeds if the editor doesn't exist yet
        if (input != restoredInput) {
        	restoredInput = input;

        	firePropertyChange(IWorkbenchPartConstants.PROP_INPUT);
        }
        
        return true;
    }

    /**
     * Reports a recoverable malfunction in the system log. A recoverable malfunction would be
     * something like failure to fire an expected property change. Only the first malfunction is
     * recorded to avoid spamming the system log with repeated failures in the same editor.
     * 
     * @since 3.1
     *
     * @param string
     */
    private void reportMalfunction(String string) {
		if (!reportedMalfunctioningEditor) {
			reportedMalfunctioningEditor = true;

			String errorMessage = "Problem detected with part " + getId(); //$NON-NLS-1$
			if (part != null) {
				errorMessage += " (class = " + part.getClass().getName() + ")"; //$NON-NLS-1$ //$NON-NLS-2$
			}

			errorMessage += ": " + string; //$NON-NLS-1$

			StatusManager.getManager().handle(
					StatusUtil.newStatus(getDescriptor().getPluginId(),
							errorMessage, null));
		}
	}

    private IEditorPart createPartHelper() throws PartInitException {
        
        // Things that will need to be disposed if an exception occurs (listed
		// in the order they
        // need to be disposed, and set to null if they haven't been created yet)
        Composite content = null;
        IEditorPart part = null;
        EditorActionBars actionBars = null;
        EditorSite site = null;
        
        try {
            IEditorInput editorInput = getEditorInput();
            
            // Get the editor descriptor.
            String editorID = getId();
            EditorDescriptor desc = getDescriptor();
            
            if (desc == null) {
                throw new PartInitException(NLS.bind(WorkbenchMessages.EditorManager_missing_editor_descriptor, editorID));
            }
            
            
            if (desc.isInternal()) {
                // Create an editor instance.
                try {
                    UIStats.start(UIStats.CREATE_PART, editorID);
                    part = manager.createPart(desc);
                    
                    // MultiEditor backwards compatibility
                    if (part != null && part instanceof MultiEditor) {
    					multiEditorChildren = manager.openMultiEditor(this,
    						(AbstractMultiEditor) part, (MultiEditorInput) editorInput);
    				}
                    if (part instanceof IWorkbenchPart3) {
                    	createPartProperties((IWorkbenchPart3)part);
                    }
                } finally {
                    UIStats.end(UIStats.CREATE_PART, this, editorID);
                }
                
            } else if (desc.getId().equals(
                    IEditorRegistry.SYSTEM_INPLACE_EDITOR_ID)) {
                
                part = ComponentSupport.getSystemInPlaceEditor();
                
                if (part == null) {
                    throw new PartInitException(WorkbenchMessages.EditorManager_no_in_place_support);
                }
            } else {
                throw new PartInitException(NLS.bind(WorkbenchMessages.EditorManager_invalid_editor_descriptor, editorID));
            }
            // Create a pane for this part
            PartPane pane = getPane();
    
            pane.createControl(getPaneControlContainer());
            
            // Create controls
            int style = SWT.NONE;
            if(part instanceof IWorkbenchPartOrientation){
                style = ((IWorkbenchPartOrientation) part).getOrientation();
            }
    
            // Link everything up to the part reference (the part reference itself should not have
            // been modified until this point)
            site = manager.createSite(this, part, desc, editorInput);
            
            // if there is saved state that's appropriate, pass it on
            if (part instanceof IPersistableEditor && editorState != null) {
				((IPersistableEditor) part).restoreState(editorState);
			}
            
            // Remember the site and the action bars (now that we've created them, we'll need to dispose
            // them if an exception occurs)
            actionBars = (EditorActionBars) site.getActionBars();
            
            Composite parent = (Composite)pane.getControl();
			EditorDescriptor descriptor = getDescriptor();
			if (descriptor != null && descriptor.getPluginId() != null) {
				parent.setData(new ContributionInfo(descriptor.getPluginId(),
						ContributionInfoMessages.ContributionInfo_Editor, null));
			}
            content = new Composite(parent, style);
    
            content.setLayout(new FillLayout());
    
            try {
                UIStats.start(UIStats.CREATE_PART_CONTROL, editorID);
                part.createPartControl(content);
            
                parent.layout(true);
            } finally {
                UIStats.end(UIStats.CREATE_PART_CONTROL, part, editorID);
            }

            // Create the inner editors of an AbstractMultiEditor (but not MultiEditor) here
            // MultiEditor backwards compatibility
            if (part != null && part instanceof AbstractMultiEditor && !(part instanceof MultiEditor)) {
				multiEditorChildren = manager.openMultiEditor(this,
					(AbstractMultiEditor) part, (MultiEditorInput) editorInput);
			}
            
            // The editor should now be fully created. Exercise its public interface, and sanity-check
            // it wherever possible. If it's going to throw exceptions or behave badly, it's much better
            // that it does so now while we can still cancel creation of the part.
            PartTester.testEditor(part);
            
            return part;
            
        } catch (Exception e) {
            // Dispose anything which we allocated in the try block
            if (content != null) {
                try {
					content.dispose();
				} catch (RuntimeException re) {
					StatusManager.getManager().handle(
							StatusUtil.newStatus(WorkbenchPlugin.PI_WORKBENCH,
									re));
				}
            }
    
            if (part != null) {
                try {
                    part.dispose();
                } catch (RuntimeException re) {
					StatusManager.getManager().handle(
							StatusUtil.newStatus(WorkbenchPlugin.PI_WORKBENCH,
									re));
				}
            }
            
            if (actionBars != null) {
                try {
                    manager.disposeEditorActionBars(actionBars);
                } catch (RuntimeException re) {
					StatusManager.getManager().handle(
							StatusUtil.newStatus(WorkbenchPlugin.PI_WORKBENCH,
									re));
				}
            }
            
            if (site != null) {
                try {
                    site.dispose();
                } catch (RuntimeException re) {
					StatusManager.getManager().handle(
							StatusUtil.newStatus(WorkbenchPlugin.PI_WORKBENCH,
									re));
				}
            }
            
            throw new PartInitException(StatusUtil.getLocalizedMessage(e), StatusUtil.getCause(e));
        }
    
    }

	protected Composite getPaneControlContainer() {
		return (Composite) manager.page.getEditorPresentation().getLayoutPart().getControl();
	}
    
    /**
     * A quick way of finding out if this reference points to a AbstractMultiEditor.
     * It depends on the fact that a AbstractMultiEditor does not lazily
     * instantiate it's child editors.
     * 
     * @return true if it has inner editor reference or the input is
     * MultiEditorInput.
     */
    public boolean isMultiReference() {
    	return multiEditorChildren!=null || restoredInput instanceof MultiEditorInput;
    }

	/**
	 * Creates and returns an empty editor (<code>ErrorEditorPart</code>).
	 * 
	 * @param descr the editor descriptor
	 * @return the empty editor part or <code>null</code> in case of an exception
	 */
	public IEditorPart getEmptyEditor(EditorDescriptor descr) {
		return getEmptyEditor(descr, null);
	}
	
	/**
	 * Creates and returns an empty editor (<code>ErrorEditorPart</code>).
	 * 
	 * @param descr the editor descriptor
	 * @param displayStatus the error status to display in the fake editor
	 * @return the empty editor part or <code>null</code> in case of an exception
	 */
	public IEditorPart getEmptyEditor(EditorDescriptor descr, IStatus displayStatus) {
		if (descr == null) {
			descr = getDescriptor(EditorRegistry.EMPTY_EDITOR_ID);
		}
		
        ErrorEditorPart part = new ErrorEditorPart(displayStatus);
        
        IEditorInput input;
        try {
            input = getEditorInput();
        } catch (PartInitException e1) {
			input = new NullEditorInput(this);
        }
        
        EditorPane pane = (EditorPane)getPane();
        
        pane.createControl(getPaneControlContainer());
        
        EditorSite site = new EditorSite(this, part, manager.page, descr);
        if ((descr != null)) {
        	// Attempt to maintain the editor's id
        	site.setId(getId());
        }
                
        site.setActionBars(new EditorActionBars(manager.page, site.getWorkbenchWindow(), getId()));

		part.init(site, input);

        Composite parent = (Composite)pane.getControl();
        Composite content = new Composite(parent, SWT.NONE);
        content.setLayout(new FillLayout());
        
        try {
			part.createPartControl(content);
		} catch (Exception e) {
			content.dispose();
			StatusManager.getManager().handle(
					StatusUtil.newStatus(WorkbenchPlugin.PI_WORKBENCH, e));
			return null;
		}

        this.part = part;
        // Add a dispose listener to the part. This dispose listener does nothing but log an exception
        // if the part's widgets get disposed unexpectedly. The workbench part reference is the only
        // object that should dispose this control, and it will remove the listener before it does so.

        if (displayStatus == null)
        	part.setPartName("(Empty)"); //$NON-NLS-1$
        refreshFromPart();
        releaseReferences();
        
        if (((WorkbenchPage)getPage()).getActiveEditorReference()!=this) {
        	fireInternalPropertyChange(INTERNAL_PROPERTY_OPENED);
        }
        
        return part;
	}
}
