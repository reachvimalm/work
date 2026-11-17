template <typename T, uint64_t SIZE>
struct ObjPool
{
	struct Slot
	{
		T d_obj;
		Slot *d_next;
		Slot():d_next(nullptr){}
	};

	Slot *d_head;
	vector<Slot> d_buf;
	void init();
	ObjPool():d_buf(SIZE)
	{
		static_assert(SIZE>0);
		for (uint64_t idx=1; idx<SIZE;++idx)
		{
			d_buf[idx-1].d_next=d_buf[idx];
		}
		d_head=&d_buf[0];
	}
	optional<T*> getNext()
	{
		if(d_head == nulltr)
		{
			return nullopt;
		}
		Slot *tmp=d_head;
		d_head=d_head->d_next;
		return &tmp->d_obj;
	}
	void release(T *obj)
	{
		Slot *tmp=static_cast<Slot*>(obj);
		tmp->d_next=d_head;
		d_head = tmp;
	}
};
