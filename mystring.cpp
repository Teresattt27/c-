/*
自定义字符串类
*/
#include <iostream>
using namespace std;

class mystring
{
friend ostream& operator <<(ostream& out,mystring str);
friend istream& operator >>(istream& in,mystring& str);
public:
	//定义迭代器
	typedef char* iterator;
	typedef const char* const_iterator;
	typedef char* reverse_iterator;
	/*
	以下函数为构造函数
	*/
	//构造函数 --无参构造
	mystring()
	{
		data=NULL;
		length=0;
	}
	//string( size_type length, char ch );以length为长度的ch的拷贝（即length个ch）
	mystring(int len,char ch)
	{
		data=new char[len+1];
		int i;
		for(i=0;i<len;i++)
		{
			data[i]=ch;
		}
	}
	//string( const char *str );以str为初值 (长度任意)
	mystring(const char * str)
	{
		if(str == NULL)
		{
			data=new char[1];
			*data='\0';
		}
		else
		{
			length=mystrlen(str);
			data=new char[length+1];
			mystrcpy(data,str);
		}
	}

	//string( const char *str, size_type length );以str为初值,长度为length
	mystring(const char * str,int len)
	{
		if(str == NULL)
		{
			data=new char[1];
			*data='\0';
		}
		else
		{
			int str_len=mystrlen(str);
			//此处注意判断设置的长度是否超过字符串长度
			if(str_len<len)
			{
				len=str_len;
			}
			length=len;
			data=new char[length+1];
			mystrncpy(data,str,length);
		}
	}

	//string( string &str, size_type index, size_type length );
	//以index为索引开始的子串，长度为length
	mystring(mystring &str,int index,int len)
	{
		if(str.data == NULL)
		{
			data=new char[1];
			*data='\0';
		}
		else
		{
			int str_len=str.length;
			if(len > (str_len-index))
			{
				len=str_len-index;
			}
			data=new char[len+1];
			int i;
			for(i=0;i<len;i++)
			{
				data[i]=str.data[index+i];
			}
			data[i]='\0';
		}
	}

	//string( input_iterator start, input_iterator end );
	//以从start到end的元素为初值.此处用到了迭代器 要考虑
	mystring(iterator start,iterator end)
	{
		mystring::iterator it;
		int i=0;
		for(it=start;it<end;it++)
		{
			i++;
		}
		this->length=i;
		this->data=new char[this->length+1];
		i=0;
		for(it=start;it<end;it++)
		{
			this->data[i]=*it;
			i++;
		}
		this->data[i]='\0';
	}



	/*
	以下函数为操作符
	*/
	bool operator ==(const mystring & str)
	{
		if(!mystrcmp(this->data,str.data))
			return true;
		else
			return false;
	}

	bool operator >(const mystring & str)
	{
		if(mystrcmp(this->data,str.data)==1)
			return true;
		else
			return false;
	}

	bool operator <(const mystring & str)
	{
		if(mystrcmp(this->data,str.data)==-1)
			return true;
		else
			return false;
	}

	bool operator >=(const mystring & str)
	{
		if((mystrcmp(this->data,str.data)==1) || (!mystrcmp(this->data,str.data)))
			return true;
		else
			return false;
	}

	bool operator <=(const mystring & str)
	{
		if((mystrcmp(this->data,str.data)==-1) || (!mystrcmp(this->data,str.data)))
			return true;
		else
			return false;
	}

	bool operator !=(const mystring & str)
	{
		if(!mystrcmp(this->data,str.data))
			return false;
		else
			return true;
	}

	mystring operator +(const mystring & str)
	{
		int len1=this->length;
		int len2=str.length;
		mystring tmp;
		tmp.length=len1+len2;
		tmp.data=new char[tmp.length+1];
		mystrcpy(tmp.data,this->data);
		mystrcat(tmp.data,str.data);
		return tmp;
	}

	mystring operator +=(mystring &str)
	{
		int len1=this->length;
		int len2=mystrlen(str.data);
		mystring tmp;
		tmp.length=len1+len2;
		tmp.data=new char[tmp.length+1];
		mystrcpy(tmp.data,this->data);
		mystrcat(tmp.data,str.data);
		if(this->data!=NULL)
		{
			delete[] this->data;
			this->data=NULL;
		}
		*this=tmp;
		return tmp;
	}

	char operator [](const int index)
	{
		return this->data[index];
	}

	/*
	以下为添加文本
	*/
	//basic_string &append( const basic_string &str );
	//在字符串的末尾添加str
	mystring &append(const mystring &str)
	{
		int len1=this->length;
		int len2=str.length;
		mystring tmp;
		tmp.length=len1+len2;
		tmp.data=new char[tmp.length+1];
		mystrcpy(tmp.data,this->data);
		mystrcat(tmp.data,str.data);
		if(this->data!=NULL)
		{
			delete this->data;
			this->data=NULL;
		}
		*this=tmp;
		return *this;
	}

	//basic_string &append( const char *str );
    //在字符串的末尾添加str
    mystring &append(const char *str)
    {
    	int len1=this->length;
    	int len2=mystrlen(str);
    	mystring tmp;
    	tmp.length=len1+len2;
    	tmp.data=new char[tmp.length+1];
    	mystrcpy(tmp.data,this->data);
    	mystrcat(tmp.data,str);
    	if(this->data!=NULL)
    	{
    		delete this->data;
    		this->data=NULL;
    	}
    	*this=tmp;
    	return *this;
    }

    //basic_string &append( const basic_string &str, size_type index, size_type len );
    //在字符串的末尾添加str的子串,子串以index索引开始，长度为len
    mystring &append(const mystring &str,int index,int len)
    {
    	int len1=this->length;
    	mystring tmp;
    	tmp.length=len1+len;
    	tmp.data=new char[tmp.length+1];
    	mystrcpy(tmp.data,this->data);
    	int i;
    	int j=0;
    	int len2=index+len;
    	for(i=index;i<len2;i++)
    	{
    		tmp.data[len1+j]=str.data[i];
    		j++;
    	}
    	tmp.data[len1+j]='\0';
    	if(this->data!=NULL)
    	{
    		delete this->data;
    		this->data=NULL;
    	}
    	*this=tmp;
    	return *this;

    }

    //basic_string &append( size_type num, char ch );
    //在字符串的末尾添加num个字符ch
    mystring &append(int num,char ch)
    {
    	mystring tmp;
    	tmp.length=this->length+num;
    	tmp.data=new char[tmp.length+1];
    	mystrcpy(tmp.data,this->data);
    	int i;
    	for(i=0;i<num;i++)
    	{
    		tmp.data[this->length+i]=ch;
    	}
    	tmp.data[this->length+i]='\0';
    	if(this->data!=NULL)
    	{
    		delete this->data;
    		this->data=NULL;
    	}
    	*this=tmp;
    	return *this;
    }

    /*
    以下为赋值操作符
    */
    //basic_string &assign( const basic_string &str );
    //用str为字符串赋值
    mystring &assign(const mystring &str)
    {
    	this->length=str.length;
    	this->data=new char[this->length+1];
    	mystrcpy(this->data,str.data);
    	return *this;
    }

    //basic_string &assign( const char *str, size_type num );
    //用str的开始num个字符为字符串赋值
    mystring &assign(const char *str,int num)
    {
    	this->length=num;
    	this->data=new char[this->length+1];
    	int i;
    	for(i=0;i<num;i++)
    	{
    		this->data[i]=str[i];
    	}
    	this->data[i]='\0';
    	return *this;
    }

    //basic_string &assign( const basic_string &str, size_type index, size_type len );
    //用str的子串为字符串赋值,子串以index索引开始，长度为len 
    mystring &assign(const mystring &str,int index,int len)
    {
    	this->length=len;
    	this->data=new char[this->length+1];
    	int i,j;
    	for(i=index,j=0;j<len;j++,i++)
    	{
    		this->data[j]=str.data[i];
    	}
    	this->data[j]='\0';
    	return *this;
    }

    //reference at( size_type index );
    //at()函数返回一个引用，指向在index位置的字符. 如果index不在字符串范围内,
    //at() 将报告"out of range"错误，并抛出out_of_range异常
    char& at(int index)
    {
    	if(index > this->length)
    	{
    		char *p="out of range";
    		cout<<p<<endl;
    		// return *p;
    	}
    	return this->data[index];
    }

    //begin
    //begin()函数返回一个迭代器,指向字符串的第一个元素.
    //待考虑
    iterator begin()
    {
    	return data;
    }

    //end
    //待考虑
    iterator end()
    {
    	return data+length;
    }

    //const char *c_str();
    //返回一个指向正规C字符串的指针, 内容与本字符串相同. 
    const char *c_str()
    {
    	return (NULL == this->data ? "" : this->data);
    }

    //size_type size();
    //返回字符串中现在拥有的字符数
    int size()
    {
    	int len=mystrlen(this->data);
    	return len;
    }

    //size_type length();
    //返回字符串的长度. 这个数字应该和size()返回的数字相同
    int slength()
    {
    	return this->size();
    }

    //size_type capacity();
    //返回在重新申请更多的空间前字符串可以容纳的字符数. 
    //这个数字至少与 size()一样大
    //不理解
    int capacity()
    {
    	int tmp=this->size();
    	if(this->length > tmp)
    		return this->length;
    	else
    		return this->size();
    }

    /*
    以下为比较
    返回值 情况 
    小于零 this < str 
    零 this == str 
    大于零 this > str 
    */
    //int compare( const basic_string &str );
    //比较自己和str
    int compare(const mystring &str)
    {
    	int len=mystrcmp(this->data,str.data);
    	return len;
    }

    //int compare( size_type index, size_type length, const basic_string &str );
    //比较自己的子串和str,子串以index索引开始，长度为length 
    int compare(int index,int length,const mystring& str)
    {
    	char *p=new char[length+1];
    	this->mycopy(p,length,index);
    	int len=mystrcmp(p,str.data);
    	return len;
    }

    //const char *data();
    //返回指向自己的第一个字符的指针
    const char *mdata()
    {
    	char *p=new char[2];
    	*p=this->data[0];
    	return p;
    }

    //bool empty();
    //如果字符串为空则empty()返回真(true)，否则返回假(false).
    bool empty()
    {
    	if(this->data==NULL)
    		return true;
    	else
    		return false;
    }

    /*
    以下为删除函数
    */
    //删除pos指向的字符, 返回指向下一个字符的迭代器,
    iterator erase( iterator pos )
    {
    	return erase(pos,pos+1);
    }

    //删除从start到end的所有字符, 返回一个迭代器,指向被删除的最后一个字符的下一个位置 
    iterator erase( iterator start, iterator end )
    {
    	mystring head(this->begin(),start);
    	mystring tail(end,this->end());
    	mystring str;
    	str=head+tail;
    	*this=str;
    	return end;
    }

    //basic_string &erase( size_type index = 0, size_type num = npos );
    //只带有index以删除index后的所有字符，或者不带有任何参数以删除所有字符
    mystring & erase(int index=0,int num=0)
    {
    	//mystring(const char * str,int len)
    	mystring head(this->data,index);
    	char *p=this->data;
    	int i=0;
    	while(i<(index+num))
    	{
    		i++;
    		p++;
    	}
    	mystring tail(p);
    	mystring c;
    	c=head+tail;
    	*this=c;
    	return *this;
    }

    /*
    以下为查找函数
    */
    //size_type find( const basic_string &str, size_type index );
    //返回str在字符串中第一次出现的位置（从index开始查找）。
    //如果没找到则返回string::npos
    int find(const mystring &str,int index)
    {
    	int len=str.length;
    	int len2=this->length-index;
    	int i,j;
    	for(i=0;i<len2;i++)
    	{
    		j=0;
    		while(this->data[index+i+j]==str.data[j])
    			j++;
    		if(j==len)
    			return (index+i+j-len);
    		else 
    			continue;
    	}
    	return -1;
    }

    //size_type find( const char *str, size_type index,size_type length );
    //返回str在字符串中第一次出现的位置（从index开始查找，长度为length）
    //如果没找到就返回string::npos
    int find(const char * str,int index,int flen)
    {
    	int len1=mystrlen(str);
    	int  i,j;
    	for(i=0;i<flen;i++)
    	{
    		j=0;
    		while(this->data[index+i+j]==str[j])
    			j++;
    		if(j==len1)
    			return (index+i+j-len1);
    		else
    			continue;
    	}
    	return -1;
    }

    //size_type find( char ch, size_type index );
    //返回字符ch在字符串中第一次出现的位置（从index开始查找）。
    //如果没找到就返回string::npos
    int find(char ch,int index)
    {
    	int len=this->length;
    	int i;
    	for(i=0;i<len-index;i++)
    	{
    		if(this->data[index+i]==ch)
    			return i;
    	}
    	return -1;
    } 

    /*
    以下为find_first_of
    */
    //size_type find_first_of( const basic_string &str, size_type index = 0 );
    //查找在字符串中第一个与str中的某个字符匹配的字符，返回它的位置
    //搜索从index开始，如果没找到就返回string::npos
    int find_first_of(const mystring &str,int index=0)
    {
    	int len1=this->length;
    	int len2=str.length;
    	int i;
    	mystring tmp=str;
    	for(i=index;i<len1;i++)
    	{
    		int k=tmp.find(this->data[i],0);
    		if(k!=-1)
    			return i;
    		else
    			continue;
    	}
    	return -1;
    } 

    //size_type find_first_of( const char *str, size_type index, size_type num );
    //查找在字符串中第一个与str中的某个字符匹配的字符，返回它的位置。
    //搜索从index开始，最多搜索num个字符。如果没找到就返回string::npos
    int find_first_of(const char *str,int index,int num)
    {
    	mystring tmp=str;
    	int len1=tmp.length;
    	int i;
    	for(i=index;i<num;i++)
    	{
    		int k=tmp.find(this->data[i],0);
    		if(k!=-1)
    			return i;
    		else
    			continue;
    	}
    	return -1;
    }

    /*
    以下为
    find_first_not_of 
    */
    //size_type find_first_not_of( const basic_string &str, size_type index = 0 );
    //在字符串中查找第一个与str中的字符都不匹配的字符，返回它的位置。搜索从index开始。
    //如果没找到就返回string::nops
    int find_first_not_of(const mystring &str,int index=0)
    {
    	int i=index;
    	int len1=this->length;
    	mystring tmp=str;
    	int len2=tmp.length;
    	int j;
    	int flag=0;  //flag 为1 表示不匹配 0表示匹配
    	for(i;i<len1;i++)
    	{
    		for(j=0;j<len2;j++)
    		{
    			if(this->data[i]==tmp.data[j])
    			{	
    				flag=0;
   					break;
   				}
    			else
    				flag=1;
    		}
    		if(flag==1)
    			return i;
    		else
    			continue;
    	}
    	return -1;
    } 

    //size_type find_first_not_of( const char *str, size_type index, size_type num );
    //在字符串中查找第一个与str中的字符都不匹配的字符，返回它的位置。
    //搜索从index开始，最多查找num个字符。如果没找到就返回string::nops 
    int find_first_not_of(const char *str,int index,int num)
    {
    	int i=index;
    	int len=mystrlen(str);
    	int j;
    	int flag=0;
    	for(i=index;i<num;i++)
    	{
    		for(j=0;j<len;j++)
    		{
    			printf("str=%c\t",this->data[i]);
    			printf("str2=%c\n",str[j]);
    			if(this->data[i]==str[j])
    			{
    				flag=0;
    				break;
    			}
    			else
    				flag=1;
    		}
    		if(flag==1)
    		{
    			return i;
    		}
    		else
    			continue;
    	}
    	return -1;
    }

    /*
    以下为
    find_last_of
    */
    //size_type find_last_of( const basic_string &str, size_type index = npos );
    //在字符串中查找最后一个与str中的某个字符匹配的字符，返回它的位置。
    //搜索从index开始。如果没找到就返回string::nops 
    int find_last_of(const mystring& str,int index=0)
    {
    	int len1=this->length;
    	mystring tmp=str;
    	int len2=tmp.length;
    	int i=index;
    	int j=0;
    	int pos=-1;
    	for(i;i<len1;i++)
    	{
    		for(j=0;j<len2;j++)
    		{
    			if(this->data[i]==tmp.data[j])
    			{
    				pos=i;
    				continue;
    			}
    		}
    	}
    	return pos;
    }

    //size_type find_last_of( const char *str, size_type index, size_type num );
    //在字符串中查找最后一个与str中的某个字符匹配的字符，返回它的位置。
    //搜索从index开始，最多搜索num个字符。如果没找到就返回string::nops 
    int find_last_of(const char *str,int index,int num)
    {
    	int len=mystrlen(str);
    	int i=index;
    	int j=0;
    	int pos=-1;
    	for(i;i<num;i++)
    	{
    		for(j=0;j<len;j++)
    		{
    			if(this->data[i]==str[j])
    			{
    				pos=i;
    				continue;
    			}
    		}
    	}
    	return pos;
    }

    /*
    以下为
    find_last_not_of 
    */
    //size_type find_last_not_of( const basic_string &str, size_type index = npos );
    //在字符串中查找最后一个与str中的字符都不匹配的字符，返回它的位置。
    //搜索从index开始。如果没找到就返回string::nops 
    int find_last_not_of(const mystring& str,int index=0)
    {
    	int len1=this->length;
    	mystring tmp=str;
    	int len2=tmp.length;
    	int i=index;
    	int j=0;
    	int pos=-1;
    	int flag=-1;
    	for(i;i<len1;i++)
    	{
    		for(j=0;j<len2;j++)
    		{
    			if(this->data[i]==tmp.data[j])
    			{
    			    pos=-1;
    				break;
    			}
    			else
    			{
    				pos=i;
    				if(j==len2-1)
    					flag=pos;
    			}
    		}
    	}
    	return flag;
    }

    //size_type find_last_not_of( const char *str, size_type index, size_type num );
    //在字符串中查找最后一个与str中的字符都不匹配的字符，返回它的位置。
    //搜索从index开始，最多查找num个字符如果没找到就返回string::nops 
    int find_last_not_of(const char*str,int index,int num)
    {
    	int len=mystrlen(str);
    	int i=index;
    	int j=0;
    	int pos=-1;
    	int flag=-1;
    	for(i;i<num;i++)
    	{
    		for(j=0;j<len;j++)
    		{
    			if(this->data[i]==str[j])
    			{
    				pos=-1;
    				break;
    			}
    			else
    			{
    				pos=i;
    				if(j==len-1)
    					flag=pos;
    			}
    		}
    	}
    	return flag;
    }

    //allocator_type get_allocator();
    //get_allocator()函数返回本字符串的配置器.


    /*
    以下为insert函数
    */
    //basic_string &insert( size_type index, const basic_string &str );
    //在字符串的位置index插入字符串str
    mystring &insert(int index,const mystring& str)
    {
    	int len=this->length - index;
    	mystring head(*this,0,index);
    	mystring tail(*this,index,len);
    	head=head+str;
    	head.mystrcat(head.data,tail.data);
    	*this=head;
    	return *this;
    }

    //basic_string &insert( size_type index1, const basic_string &str, size_type index2, size_type num );
    //在字符串的位置index插入字符串str的子串(从index2开始，长num个字符),
    mystring &insert(int index1,const mystring &str2,int index2,int num)
    {
    	int len=str2.length;
    	int i;
    	char *p=new char[num+1];
    	for(i=0;i<num;i++)
    	{
    		p[i]=str2.data[index2+i];
    	}
    	const mystring tmp(p);
    	this->insert(index1,tmp);
    	return *this;
    }

    /*
    以下为repalce函数
    */
    //basic_string &replace( size_type index, size_type num, const basic_string &str );
    //用str中的num个字符替换本字符串中的字符,从index开始 
    mystring &replace(int index,int num,const mystring &str)
    {
    	char *p=this->data;
    	int i;
    	while(i<index)
    	{
    		p++;
    		i++;
    	}
    	int j=0;
    	char *q=str.data;
    	while((num-- !=0) && ((*p++ = *q++)!= '\0'));
    	if(*p != '\0')
    		*p='\0';
    	this->length=mystrlen(this->data);
    	return *this;
    }

    // void reserve( size_type num );
    // reserve()函数设置本字符串的capacity 以保留num个字符空间
    void reserve(int num)
    {
    	this->length=num;
    }

    /*
    以下为resize
    */
    //void resize( size_type num );
    //改变本字符串的大小到num, 新空间的内容不确定
    void resize(int num)
    {
    	this->length=num;
    }

    //void resize( size_type num, char ch );
    //用ch填充
    void resize(int num,char ch)
    {
    	this->length=num;
    	int i;
    	for(i=0;i<num;i++)
    		this->data[i]=ch;
    }

    /*
    以下为rfind
    */
    //size_type rfind( const basic_string &str, size_type index );
    //返回最后一个与str中的某个字符匹配的字符，从index开始查找。如果没找到就返回string::npos 
    int rfind(const mystring& str,int index)
    {
    	int k=this->find_last_of(str,index);
    	return k;
    }

    //size_type rfind( const char *str, size_type index, size_type num );
    //返回最后一个与str中的某个字符匹配的字符，从index开始查找,最多查找num个字符。
    //如果没找到就返回string::npos
    int rfind(const char *str,int index,int num)
    {
    	int k=find_last_of(str,index,num);
    	return k;
    } 

    //basic_string substr( size_type index, size_type num = npos );
    //返回本字符串的一个子串，从index开始，长num个字符。如果没有指定，将是默认值 string::npos。
    //这样，substr()函数将简单的返回从index开始的剩余的字符串。
    mystring substr(int index,int num=-1)
    {
    	mystring tmp;
    	tmp.length=num;
    	tmp.data=new char[tmp.length+1];
    	int i;
    	for(i=0;i<num;i++)
    	{
    		tmp.data[i]=this->data[index+i];
    	}
    	return tmp;
    }

    //void swap( basic_string &str );
    //把str和本字符串交换
    void swap(mystring &str)
    {
    	mystring tmp(str);
    	str=*this;
    	*this=tmp;
    }

	//求长度的函数
	int mystrlen(const char* ch)
	{
		int len=0;
		while(*ch != '\0')
		{
			len++;
			ch++;
		}
		return len;
	}

	//拷贝
	char* mystrcpy(char* dest,const char* src)
	{
		if(dest==NULL || src==NULL)
		{
			return NULL;
		}
		char *p=dest;
		while((*p++ = *src++)!='\0');
		return dest;
	}

	//拷贝length长度
	char* mystrncpy(char* dest,const char* src,int len)
	{
		if(dest==NULL || src==NULL)
			return NULL;
		char *p=dest;
		while((len-- !=0) && ((*p++ = *src++)!='\0'));
		if(*p != '\0')
			*p='\0';
		return dest;
	}

	//copy
	//copy()函数拷贝自己的num个字符到str中
	//(从索引index开始）,返回值是拷贝的字符数
	//拷贝出错 则返回-1
	int mycopy(char* str,int num,int index)
	{
		if(this->data==NULL || str==NULL)
			return -1;
		char *p=this->data;
		int i=0;
		int j=0;
		while(i<index)
		{
			//p++;  //从自己的index
			str++;  //从str的index
			i++;
		}
		while((num-- !=0) && ((*str++ = *p++)!= '\0'))
			j++;
		if(*str !='\0')
			*str='\0';
		return j;
	}

	int mystrcmp(char const *dest,char const *src)
	{
		while((*dest!='\0') && (*src!='\0'))
		{
			if(*dest!=*src)
			{
				if(*dest>*src)
				{
					return 1;
				}
				else
					return -1;
			}
			dest++;
			src++;
		}
		if((*dest=='\0') && (*src)==0)
			return 0;
		else if((*dest!='\0') && (*src=='\0'))
			return 1;
		else
			return -1;
	}

	char* mystrcat(char *dest,char const *src)
	{
		//三种方式都能实现,但是要注意使用时要使dest空间足够大,
		//否则会发生栈溢出的现象
	    char *p=dest;
		while(*dest != '\0')
		{
			++dest;
		}
		while(*dest++ = *src++)
			NULL;
		return p;
		//------------------------
		// char *p=dest;
		// while(*dest)
		// 	dest++;
		// while(*src != '\0')
		// 	*dest++ = *src++;
		// *dest='\0';
		// cout<<dest<<endl;
		// return p;
		//---------------------------
		// int len=mystrlen(dest);
		// int i;
		// for(i=0;src[i]!='\0';i++)
		// 	dest[len+i]=src[i];
		// dest[len+i]='\0';
		// return dest;
	}


private:
	char *data;
	int length;
};
//输出
ostream& operator <<(ostream& out,mystring str)
{
	out<<str.data;
	return out;
}
//输入
istream& operator >>(istream& in,mystring& str)
{
	in>>str.data;
	return in;
}

int main(int argc, char const *argv[])
{
	char a[80]="112d23344";
	char b[]="asdfdjldsjf";
	mystring str1(a);
	mystring str2(b);
	cout<<str2.erase(1,8)<<endl;
	cout<<str2<<endl;
	return 0;
}
