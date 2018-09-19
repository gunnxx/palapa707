#include <mutex>

template <class datatype>
class ThreadSafe {
  public:
  	datatype &access_data();
  	datatype get_data();

  private:
  	datatype _data;
  	std::mutex _m;
};

template <class datatype>
datatype &ThreadSafe<datatype>::access_data(){
	std::lock_guard<std::mutex> lock(_m);
	return _data;
}

template <class datatype>
datatype ThreadSafe<datatype>::get_data(){
	std::lock_guard<std::mutex> lock(_m);
	return _data;
}