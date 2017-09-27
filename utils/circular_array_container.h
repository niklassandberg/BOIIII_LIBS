#ifndef _BO_ARRAY_CONTAINER_H_
#define _BO_ARRAY_CONTAINER_H_

template<typename T>
class array_container
{
    const size_t SIZE;

    T * mValues;

    size_t mHead;
    size_t mTail; 

public:

    array_container(size_t size) : SIZE(size), mHead(0), mTail(0)
    {
        mValues = new T[size];
        for(size_t i = 0; i < size; ++i)
        {
            mValues[i] = 0;
        }
    }

    ~array_container()
    {
        delete [] mValues;
    }

    T& operator[](size_t index) { return mValues[index]; }
    const T& operator[](size_t index) const { return mValues[index]; }

    //Return SIZE if not found
    size_t index(size_t start, T& value)
    {
        for (size_t i = start; i < mLength; i++)
        {
            if(value == mValues[i]) return i;
        }
        return SIZE;
    }

    size_t index(T& value)
    {
        return index(mHead,value);
    }

    size_t remove_at(size_t index)
    {
        if( mLength == 0 || mLength <= index ) return SIZE;
        for (size_t i = index; i < mLength; i++) {
            mValues[i] = mValues[i + 1];
        }
        --mLength;
        return index;
    }

    //TODO: another name..
    size_t insert_at(size_t index, T& value)
    {
        if( mLength+1>=SIZE || mLength < index ) return SIZE;

        for (size_t i = index; i < mLength; i++) {
            mValues[i + 1] = mValues[i];
        }
        mValues[index] = value;
        ++mLength;
        return index;
    }

    size_t push_back(T& value)
    {
        return insert_at(mLength,value);
    }

    T& peek_back( )
    {
        return mValues[mLength-1];
    }

    bool empty()
    {
        return mLength == 0;
    }

    size_t max_size()
    {
        return SIZE;
    }

    size_t size()
    {
        return mLength;
    }

};

#endif
