/*
File name:myvector
Author:Tian Tingting
Date:2016-3-22
Description:实现vector容器
*/
#include <iostream>
using namespace std;
template<class T>
class myvector
{
public:
	//定义迭代器
	typedef T* iterator;              //迭代器
	typedef const T* const_iterator;  //只读迭代器
	typedef T* reverse_iterator;      //逆向迭代器
 	typedef bool (*sortfun)(T a,T b); //定义一个函数指针

	//以下为构造函数
	myvector()
	{
		data=NULL;
		size=0;
		capacity=0;
	}

	//数量(num)和值(val) - 构造一个初始放入num个值为val的元素的Vector 
	myvector(int num, const T &val)
	{
		this->size=num;
		this->capacity=2*this->size;
		data=new T[capacity];
		int i;
		for(i=0;i<num;i++)
			data[i]=val;
	}

	//构造一个与vector from 相同的vector 
	myvector(const myvector &from)
	{
		size=from.size;
		capacity=from.capacity;
		data=new T[capacity];
		int i;
		for(i=0;i<size;i++)
		{
			data[i]=from.data[i];
		}
	}

	//迭代器(start)和迭代器(end)构造一个初始值为[start,end)区间元素的vector
	myvector(iterator start, iterator tend)
	{
		// myvector<int>::iterator it;
		myvector<int>::iterator it;
		int i=0;
		for(it=start;it!=tend;it++)
			i++;
		this->size=i;
		this->capacity=2*i;
		data=new T[this->capacity];
		i=0;
		for(it=start;it!=tend;it++)
		{
			data[i]=*it;
			i++;
		}
		data[i]='\0';
	}

	//运算符
	bool operator ==(myvector& v2)
	{
		if(this->capacity == v2.capacity)
		{
			int max;
			if(this->size > v2.size)
			{
				max=this->size;
			}
			else
			{
				max=v2.size;
			}
			int i;
			for(i=0;i<max;i++)
			{
				if(this->data[i] != v2.data[i])
				{
					return false;
				}
				else
					continue;
			}
			return true;
		}
		else
			return false;

	}

	bool operator !=(myvector& v2)
	{
		if(*this==v2)
			return false;
		else
			return true;
	}

	bool operator <(myvector& v2)
	{
		int max;
		if(this->size > v2.size)
			max=this->size;
		else
			max=v2.size;
		int i;
		for(i=0;i<max;i++)
		{
			if(this->data[i] < v2.data[i])
				return true;
			else if(this->data[i] == v2.data[i])
				continue;
			else
				return false;
		}
		return false;
	}

	bool operator >(myvector& v2)
	{
		if((*this == v2) || (*this < v2) )
			return false;
		else
			return true;
	}

	bool operator <=(myvector& v2)
	{
		if(*this > v2)
			return false;
		else
			return true;
	}

	bool operator >=(myvector& v2)
	{
		if(*this < v2)
			return false;
		else
			return true;
	}

	T& operator [](const int index)
	{
		return *(data+index);
	}

    //将区间[start, end)的元素赋到当前vector
	void assign(iterator start,iterator tend )
	{
		this->clear();
		myvector<int>::iterator it;
		int i=0;
		for(it=start;it!=tend;it++)
			i++;
		this->size=i;
		this->capacity=2*i;
		data=new T[this->capacity];
		i=0;
		for(it=start;it!=tend;it++)
		{
			data[i]=*it;
			i++;
		}
		data[i]='\0';

	}
    
    //赋num个值为val的元素到vector中
    void assign( int num, const T &val )
    {
    	this->clear();
    	this->size=num;
    	this->capacity=2*this->size;
    	this->data=new T[this->capacity];
    	int i;
    	for(i=0;i<num;i++)
    	{
    		this->data[i]=val;
    	}
    	this->data[i]='\0';
    }

    //at() 函数 返回当前Vector指定位置loc的元素的引用
    //它不会让你去访问到Vector内越界的元素
    T at(int loc)
    {
    	if(loc >= this->size)
    	{
    		cout<<"error"<<endl;
    		exit(-1);
    	}
    	else
    	{
    		return *(data+loc);
    	}
    }

	iterator begin()
	{
		return data;
	}

	iterator end()
	{
		return data+size;
	}

    //back() 函数返回当前vector最末一个元素的引用
	T back()
	{
		if(this->data!=NULL)
		{
			return *(data+size-1);
		}
		else
		{
			cout<<"data is NULL"<<endl;
			exit(-1);
		}
	}

	//capacity() 函数 返回当前vector在重新进行内存分配以前所能容纳的元素数量.
	int mycapacity()
	{
		return this->capacity;
	}

	//clear()函数删除当前vector中的所有元素.
	void clear()
	{
		this->size=0;
		this->capacity=0;
		delete this->data;
		this->data=NULL;
	}

	//如果当前vector没有容纳任何元素,则empty()函数返回true,否则返回false
	bool empty()
	{
		if(this->data==NULL)
			return true;
		else
			return false;
	}

	//front()函数返回当前vector起始元素的引用
	T front()
	{
		if(this->data!=NULL)
		{
			return *(this->data);
		}
		else
		{
			cout<<"data is NULL"<<endl;
			exit(-1);
		}
	}

	//返回当前vector所能容纳元素数量的最大值
	int max_size()
	{
		return this->capacity;
	}

	//pop_back()函数删除当前vector最末的一个元素
	void pop_back()
	{
		myvector<int>::iterator it;
		it=this->end();
		it--;
		erase(it);
	}

	//删作指定位置loc的元素
	//返回值是指向删除的最后一个元素的下一位置的迭代器
	iterator erase(iterator loc)
	{
		if((loc < this->begin()) || (loc > this->end()))
		{
			cout<<"error"<<endl;
			exit(-1);
		}
		else
		{
			myvector<int>::iterator it;
			myvector<int>::iterator qp;
			it=loc;
			qp=loc;
			qp++;
			while(it != this->end())
			{
				*it++ = *(it+1);
			}
			this->size=this->size-1;
			this->capacity=2*this->size;
			return qp;
		}
	}

	//删除区间[start, end)的所有元素
	iterator erase( iterator start, iterator tend)
	{
		if((start < this->begin()) || (tend > this->end()))
		{
			cout<<"error"<<endl;
			exit(-1);
		}
		else
		{
			myvector<int>::iterator it;
			for(it=start;it!=tend;it++)
			{
				this->erase(it);
			}
			return it;
		}
	}

	//在指定位置loc前插入值为val的元素,返回指向这个元素的迭代器, 
	iterator insert(iterator loc,const T& val)
	{
		if((loc < this->begin()) || (loc > this->end()))
		{
			cout<<"error"<<endl;
			exit(-1);
		}
		else
		{
			this->size=this->size+1;
			this->capacity=2*this->size;
			myvector<int>::iterator it;
			it=loc;
			T tmp;
			tmp=*it;
			*it=val;
			it++;
			for(it;it!=this->end();it++)
			{
				T sav=*it;
				*it=tmp;
				tmp=sav;
			}
		}
		return loc;
	}

	//在指定位置loc前插入num个值为val的元素
	void insert(iterator loc, int num, const T &val )
	{
		int i;
		for(i=0;i<num;i++)
		{
			insert(loc,val);
		}
	}

	//在指定位置loc前插入区间[start, end)的所有元素 . 
	void insert( iterator loc,iterator start,iterator tend)
	{
		myvector<int>::iterator it;
		for(it=start;it!=tend;it++)
		{
			insert(loc,*it);
		}
	}

    //添加值为val的元素到当前vector末尾
	void push_back( const T &val )
	{
		myvector<int>::iterator it;
		it=this->end();
		insert(it,val);
	}

	//返回指向当前vector末尾的逆迭代器.
	reverse_iterator rbegin()
	{
		return data+size;
	}

	//rend()函数返回指向当前vector起始位置的逆迭代器. 
	reverse_iterator rend()
	{
		return data;
	}

	//为当前vector预留至少共容纳size个元素的空间
	void reserve( int lsize )
	{
		this->size=lsize;
		this->capacity=2*this->size;
		data=new T[this->capacity];
	}

	//改变当前vector的大小为size,且对新创建的元素赋值val
	void resize(int lsize, T val )
	{
		this->clear();
		this->size=lsize;
		this->capacity=2*this->size;
		this->data=new T[this->capacity];
		int i;
		for(i=0;i>this->size;i++)
		{
			this->data[i]=val;
		}
		this->data[i]='\0';
	}

	//返回当前vector所容纳元素的数目 
	int mysize()
	{
		return this->size;
	}

	//交换当前vector与vector from的元素
	void swap(myvector &from )
	{
		myvector<T> tmp(from);
		from=*this;
		*this=tmp;
	}

	/*
	排序:默认升序
	*/
	void sort()
	{
		int i,j;
		for(i=0;i<this->size;i++)
		{
			for(j=0;j<this->size-i-1;j++)
			{
				if(this->data[j]>this->data[j+1])
				{
					T tmp=this->data[j];
					this->data[j]=this->data[j+1];
					this->data[j+1]=tmp;
				}
			}
		}
	}

	//指定排序的方式
	void sort(sortfun fp)
	{
		int i,j;
		for(i=0;i<this->size;i++)
		{
			for(j=0;j<this->size-i-1;j++)
			{
				if(fp(this->data[j],this->data[j+1]))
				{
					T tmp=this->data[j];
					this->data[j]=this->data[j+1];
					this->data[j+1]=tmp;
				}
			}
		}
	}

	//输出全部的值
	void pop_out()
	{
		myvector<int>::iterator it;
		for(it=this->begin();it!=this->end();it++)
		{
			cout<<*it<<"\t";
		}
		cout<<endl;
	}

private:
	T* data;
	int size;
	int capacity;
};

template<class T>
bool sortdirection(T a,T b)
{
	return a>b;//升序
	//return a<b;//降序
}

int main(int argc, char const *argv[])
{
	myvector<int> v2(2,3);	
	myvector<int>::iterator qp;
	qp=v2.begin();
	v2.insert(qp,12);
	v2.insert(qp,15);
	v2.insert(qp,6);
	v2.pop_out();	
	return 0;
}
