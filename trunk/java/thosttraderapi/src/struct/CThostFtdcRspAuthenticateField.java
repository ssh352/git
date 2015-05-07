package struct;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import com.sun.jna.Structure;

/**
 * 客户端认证响应
 * 
 * @author 陈霖 2015-5-4
 */
public class CThostFtdcRspAuthenticateField extends Structure {
	/**
	 * 经纪公司代码
	 */
	public byte[] BrokerID = new byte[11];
	/**
	 * 用户代码
	 */
	public byte[] UserID = new byte[16];
	/**
	 * 用户端产品信息
	 */
	public byte[] UserProductInfo = new byte[11];

	@Override
	@SuppressWarnings("rawtypes")
	protected List getFieldOrder() {
		Field[] fields = this.getClass().getDeclaredFields();
		List<String> names = new ArrayList<String>(fields.length);
		for (int i = 0; i < fields.length; i++) {
			names.add(fields[i].getName());
		}
		return names;
	}

	/**
	 * 指针
	 */
	public static class ByReference extends CThostFtdcRspAuthenticateField implements Structure.ByReference {
	}

	/**
	 * 值
	 */
	public static class ByValue extends CThostFtdcRspAuthenticateField implements Structure.ByValue {
	}
}
