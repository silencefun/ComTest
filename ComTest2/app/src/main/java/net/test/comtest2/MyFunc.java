package net.test.comtest2;

/**
 * @author benjaminwan
 *����ת������
 */
public class MyFunc {
	//-------------------------------------------------------
	// �ж�������ż����λ���㣬���һλ��1��Ϊ������Ϊ0��ż��
    static public int isOdd(int num)
	{
		return num & 0x1;
	}
    //-------------------------------------------------------
    static public int HexToInt(String inHex)//Hex�ַ���תint
    {
    	return Integer.parseInt(inHex, 16);
    }
    //-------------------------------------------------------
    static public byte HexToByte(String inHex)//Hex�ַ���תbyte
    {
    	return (byte)Integer.parseInt(inHex,16);
    }
    //-------------------------------------------------------
    static public String Byte2Hex(Byte inByte)//1�ֽ�ת2��Hex�ַ�
    {
    	return String.format("%02x", inByte).toUpperCase();
    }
    //-------------------------------------------------------
	static public String ByteArrToHex(byte[] inBytArr)//�ֽ�����תתhex�ַ���
	{
		StringBuilder strBuilder=new StringBuilder();
		int j=inBytArr.length;
		for (int i = 0; i < j; i++)
		{
			strBuilder.append(Byte2Hex(inBytArr[i]));
			strBuilder.append(" ");
		}
		return strBuilder.toString(); 
	}
  //-------------------------------------------------------
    static public String ByteArrToHex(byte[] inBytArr,int offset,int byteCount)//�ֽ�����תתhex�ַ�������ѡ����
	{
    	StringBuilder strBuilder=new StringBuilder();
		int j=byteCount;
		for (int i = offset; i < j; i++)
		{
			strBuilder.append(Byte2Hex(inBytArr[i]));
		}
		return strBuilder.toString();
	}
	//-------------------------------------------------------
	//תhex�ַ���ת�ֽ�����
    static public byte[] HexToByteArr(String inHex)//hex�ַ���ת�ֽ�����
	{
		int hexlen = inHex.length();
		byte[] result;
		if (isOdd(hexlen)==1)
		{//����
			hexlen++;
			result = new byte[(hexlen/2)];
			inHex="0"+inHex;
		}else {//ż��
			result = new byte[(hexlen/2)];
		}
	    int j=0;
		for (int i = 0; i < hexlen; i+=2)
		{
			result[j]=HexToByte(inHex.substring(i,i+2));
			j++;
		}
	    return result; 
	}
}