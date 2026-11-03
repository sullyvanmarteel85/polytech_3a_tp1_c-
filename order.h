#ifndef ORDER_H
#define ORDER_H
#define SPEED_MAX 240

class Order
{
	public:
		Order(short left=0, short right=0);
		short get_order_R() const;
		short get_order_L() const;
		void set_order(short left, short right);
	private:
		short m_order_L;
		short m_order_R;
		void limit();

};

#endif
