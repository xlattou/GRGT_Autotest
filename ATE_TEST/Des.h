//////////////////////////////////////////////////////////////////////////
/*
This product is free for use.
*/
//////////////////////////////////////////////////////////////////////////
#ifndef Des_H
#define Des_H

//! enum    bool{false,true}; 
/*!  
if bool is not supported,use this or just replace with char and use 1 for true,0 for false;
@see enum    {ENCRYPT,DECRYPT};
*/
enum    {ENCRYPT,DECRYPT};
/*@brief  16Ȧ����Կ*/
static bool SubKey[2][16][48];// 16Ȧ����Կ
/*@brief 3��DES��־*/
static bool Is3DES;// 3��DES��־
static char Tmp[256];
static char deskey[16];
typedef bool    (*PSubKey)[16][48];

class _declspec(dllexport) Des
{
public:
	Des();
	~Des();
	//! Type��ENCRYPT:����,DECRYPT:����
	/*! 
	���������(Out)�ĳ��� >= ((datalen+7)/8)*8,����datalen�������8�ı�������С������
	In ����= Out,��ʱ��/���ܺ󽫸������뻺����(In)������
	��keylen>8ʱϵͳ�Զ�ʹ��3��DES��/����,����ʹ�ñ�׼DES��/����.����16�ֽں�ֻȡǰ16�ֽ�
	@see bool Des_Go(char *Out,char *In,long datalen,const char *Key,int keylen,bool Type = ENCRYPT);
	*/
	
	bool Des_Go(char *Out,char *In,long datalen,const char *Key,int keylen,bool Type = ENCRYPT);
	
private:
/*! @brief ��׼DES��/����
@see static void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type);
	*/
	static void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type);//��׼DES��/����
																			   /*! @brief ������Կ
																			   @see static void SetKey(const char* Key, int len);
	*/
	static void SetKey(const char* Key, int len);// ������Կ
												 /*! @brief ��������Կ
												 @see static void SetSubKey(PSubKey pSubKey, const char Key[8]);
	*/
	static void SetSubKey(PSubKey pSubKey, const char Key[8]);// ��������Կ
															  /*! @brief f ����
															  @see static void F_func(bool In[32], const bool Ki[48]);
	*/
	static void F_func(bool In[32], const bool Ki[48]);// f ����
													   /*! @brief S �д���
													   @see static void S_func(bool Out[32], const bool In[48]);
	*/
	static void S_func(bool Out[32], const bool In[48]);// S �д���
														/*! @brief �任
														@see static void Transform(bool *Out, bool *In, const char *Table, int len);
	*/
	static void Transform(bool *Out, bool *In, const char *Table, int len);// �任
																		   /*! @brief ���
																		   @see static void Xor(bool *InA, const bool *InB, int len);
	*/
	static void Xor(bool *InA, const bool *InB, int len);// ���
														 /*! @brief ѭ������
														 @see static void RotateL(bool *In, int len, int loop);
	*/
	static void RotateL(bool *In, int len, int loop);// ѭ������
													 /*! @brief �ֽ���ת����λ��
													 @see static void ByteToBit(bool *Out, const char *In, int bits);
	*/
	static void ByteToBit(bool *Out, const char *In, int bits);// �ֽ���ת����λ��
															   /*! @brief λ��ת�����ֽ���
															   @see static void BitToByte(char *Out, const bool *In, int bits);
	*/
	static void BitToByte(char *Out, const bool *In, int bits);// λ��ת�����ֽ���
	
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#endif