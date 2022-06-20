class CMyString
{
private:
	char* buffer;
	int mLen;

public:
	CMyString(const char* str, int len) : mLen(len)
	{
		buffer = new char[len + 1];
		memcpy_s(buffer, len, str, len);
		buffer[len] = '\0';
	}


	const char* getbuffer()
	{
		return buffer;
	}

	CMyString operator+(const CMyString& pStr)
	{
		int len = pStr.mLen + mLen;
		CMyString* pTemp = new CMyString("", len);

		memcpy_s(pTemp->buffer, mLen, buffer, mLen);
		memcpy_s(pTemp->buffer + mLen, pStr.mLen, pStr.buffer, pStr.mLen);

		return *pTemp;
	}

	void operator=(const CMyString& pStr)
	{
		delete buffer;
		buffer = new char(pStr.mLen + 1);
		mLen = pStr.mLen;
		memcpy_s(buffer, mLen, buffer, mLen);
		memcpy_s(buffer + mLen, pStr.mLen, pStr.buffer, pStr.mLen);
	}
};