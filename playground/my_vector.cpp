template <typename T>
class my_vector {
    private:
    T* data;
    int _size;
    int _capacity;

    public:
    my_vector() {
        data= nullptr;
        _size=0;
        _capacity=0;
    }
    ~my_vector() {
        delete[] data;
    }

    my_vector my_vector::operator=(const my_vector& other){
        if (this==&other){
            return *this;
        }else{
        delete [] this->data;
        this->_size= other._size;
        this->_capacity= other._capacity;
        this->data = new T[this->_capacity];
        for (int i=0; i<_size; i++){
            this->data[i]=other.data[i];
        }
        return * this;
        }

    }

    T& operator[](int i){
        if (i>= _size){
            cout<<"out of range"<<endl;
        }
        return data[i];
    }
    int size(){
        return _size;
    }
    int capacity(){
        return _capacity;
    }
    void clear(){
        _size=0;
    }
    void push_back(const T& newitem){
        if (_size==_capacity){
            if (_capacity==0){
                _capacity=1;
            }else{
                _capacity= _capacity*2;
            }
            T* newdata= new T[_capacity];
            for (int i=0; i<_size; i++){
                newdata[i]= data[i];
            }
            delete[] data;
            data= newdata;
            data[_size]=newitem;
            _size++;

        }else{
            data[_size]=newitem;
            _size++;
        }
        
    }
    void pop_back(){
        if (size>0){
        _size--;
        }
    }

    void insert(int index,const T& newitem){
        T* newdata= new T[_capacity+1];
            for (int i=0; i<index-1; i++){
                newdata[i]= data[i];
            }
            newdata[index-1]= newitem;
            for (int i=index; i<_size; i++){
                newdata[i]=data[i-1];
            }
            delete[] data;
            data= newdata;
            _size++;

    }

    

};
