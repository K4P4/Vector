#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

const int defaultSize = 2;

//naudojama kaip susinaikinantis pointeris
template <typename T>
class auto_array{
    private :
        T *ptr_;
    public :
        auto_array(T *t) : ptr_( t )
        { }

        ~auto_array()
        { delete[] ptr_; }

        T *operator->()
        { return ptr_; }

        T *release()
        {
            T *tmp( ptr_ );
            ptr_ = 0;
            return tmp;
        }

        T &operator[](int i)
        { return ptr_[i]; }
};

template <typename T>
class Vector
{
    private :
        T *array_;
        int size_;
        int reserved_size_;
    public:
        Vector() //Default konstruktorius kai nezinomas pradinis elementu kiekis;
            : array_( new T[defaultSize]),
            reserved_size_(defaultSize),
            size_(0) { }

        Vector(int n) //Konstruktorius kai zinomas pradinis elementu kiekis;
            : array_( new T[n] ),
            reserved_size_( n ),
            size_( 0 ) { }

        ~Vector() //Destruktorius
        { delete[] array_; }

		typedef T* iterator;

        //metodai
        void assign(int n, T value);
        void push_back(const T &t);
        void pop_back();
        iterator insert(iterator it, T value);
        void insert(iterator it, int n, T value);
        iterator erase(iterator it);
        iterator erase(iterator it1, iterator it2);
        void clear();

        T* data(){return array_;}

        void resize(int n, T val = 0);
        int size(){return size_;}
        int capacity(){return reserved_size_;}
        bool empty(){if(size_ > 0) return false; else return true;};
        void shrink_to_fit();
        void reserve(int n);

        //nuorodos
        T& at(int it) {
		if (it < 0 || size_ < it) throw std::out_of_range {"Vector::reference_at"};
		return array_[it];
        }
        T& back(){return array_[size_-1];}
        T& front(){return array_[0];}

		T* begin(){ return array_;};
		T* end(){return array_+size_;};


        //operatoriai
        T& operator[](int i) {
        if(i < size_ && i >= 0){ return array_[i]; }
        else throw std::out_of_range {"Vector::operator[]"};
        }
	};

	template <typename T>
    void Vector<T>::reserve(int n)
    {
    if(n > reserved_size_) {
        auto_array<T> new_array( new T[n] ); //sukuria nauja reikiamo dydzio masyva
        for(int i=0; i<size_; i++){ //perkopijuoja sena masyva i naujaji
            new_array[i] = array_[i];
        }

        delete[] array_; //istrina sena masyva
        array_ = new_array.release();
        reserved_size_ = n;
    }
}

	template <typename T>
    void Vector<T>::shrink_to_fit()
    {
    if(size_ < reserved_size_){
        auto_array<T> new_array( new T[size_] ); //sukuria nauja reikiamo dydzio masyva
        int k;
        for(int i=0; i<size_; i++){ //perkopijuoja sena masyva i naujaji
            new_array[i] = array_[i];
        }
        delete[] array_; //istrina sena masyva
        array_ = new_array.release();
        reserved_size_ = size_;
        }
}

    template <typename T>
    void Vector<T>::push_back(const T &t)
    {
        if(size_ == reserved_size_)
            reserve(reserved_size_*2 + defaultSize);

        array_[size_] = t;

        size_++;
    }

    template <typename T>
    void Vector<T>::resize(int n, T val)
    {
        if(n > 0){
        auto_array<T> new_array( new T[n] ); //sukuria nauja reikiamo dydzio masyva
        int k;
        if(size_ > n) k = n; else k = size_;
        for(int i=0; i<k; i++){ //perkopijuoja sena masyva i naujaji
            new_array[i] = array_[i];
        }
        for(int i=k; i<n; i++){
            new_array[i] = val;
        }

        delete[] array_; //istrina sena masyva
        array_ = new_array.release();
        if(n > reserved_size_) reserved_size_ = n;
        size_ = n;
        }
}

    template <typename T>
        void Vector<T>::pop_back()
        {
        if(size_ > 0){
            delete &array_[size_];
            size_--;
        }
    }

    template <typename T>
    void Vector<T>::assign(int n, T value){
            if (n < 0) throw std::out_of_range {"Vector::assign"};
            delete[] array_;
            size_ = n;
            reserved_size_ = size_;
            array_ = new T[size_];
            std::fill_n(array_, size_, value);
    }

    template <typename T>
    T* Vector<T>::insert(iterator it, T value){
		int i = 0;
		if (size_ < reserved_size_) {
			for(iterator itr = array_ + size_; itr != it; itr--, i++)
				array_[size_ - i] = array_[size_ - i - 1];
			*it = value;
			size_++;
		}
		else {
			auto_array<T> new_array(new T[size_ + 1]); //sukuria nauja reikiamo dydzio masyva

			for (iterator itr = array_; itr != it; itr++, i++)
				new_array[i] = array_[i];
			new_array[i] = value;
			i++;
			for (iterator itr = array_ + i + 1; itr != array_ + size_ + 2; itr++, i++)
				new_array[i] = array_[i - 1];

			delete[] array_; //istrina sena masyva
			array_ = new_array.release();
			size_++;
			reserved_size_ = size_;
		}
    }

    template <typename T>
    void Vector<T>::insert(iterator it, int n, T value){
        int i = 0;
		if (size_ + n < reserved_size_) {
			for (iterator itr = array_ + size_ + n-1; itr != it+n-1; itr--, i++)
				array_[size_ - i + n - 1] = array_[size_ - i - 1];
			for (int j = 0; j < n; j++, i++) {
				array_[size_ - i + n - 1] = value;
			}
			size_++;
		}
		else {
			auto_array<T> new_array(new T[size_ + n]); //sukuria nauja reikiamo dydzio masyva
			int i = 0, j = 0;

			for (iterator itr = array_; itr != it; itr++, i++)
				new_array[i] = array_[i];

			for (j; j < n; j++)
				new_array[i + j] = value;

			for (iterator itr = array_ + i; itr != array_ + size_; itr++, i++)
				new_array[i + j] = array_[i];

			delete[] array_; //istrina sena masyva
			array_ = new_array.release();
			size_ = size_ + n;
			if (reserved_size_ < size_) reserved_size_ = size_;
		}
    }

    template <typename T>
    void Vector<T>::clear(){
		if(size_ > 0) {
			size_ = 0;
		}
	}

	template <typename T>
    T* Vector<T>::erase(iterator it){
		int i = 0;

		for (auto itr = (*this).begin(); itr != it; itr++, i++);
		for (auto itr = it + 1; itr != (*this).end(); itr++, i++)
			array_[i] = array_[i + 1];

		size_--;
		return it;
    }

    template <typename T>
    T* Vector<T>::erase(iterator it1, iterator it2) {
		int i = 0;
		int temp = 0;

		for (auto itr = (*this).begin(); itr != it1; itr++, i++);
		for (auto itr = it1; itr != it2; itr++, temp++, i++);

		for (auto itr = it2; itr != (*this).end(); itr++, i++)
			array_[i - temp] = array_[i];

		size_ -= temp;
		return it2;
	}

#endif // VECTOR_H_INCLUDED
