struct Position2D
{
	float x;
	float y;
};

float G = 1.0f;

float m1 = 15.0f;	// Mass
float m2 = 10.0f;
float m3 = 4.0f;

float x1 = 300.0f;
float y1 = 50.0f;
float x2 = -100.0f;
float y2 = -200.0f;
float x3 = -100.0f;
float y3 = 150.0f;

float v1_x = 0.0f;
float v1_y = 0.0f;
float v2_x = 0.0f;
float v2_y = 0.0f;
float v3_x = 0.0f;
float v3_y = 0.0f;

float t = 0.1;

float qsqrt_nt( float number )
{
	float val = number;//初始值
	float last;
	do
	{
		last = val;
		val = (val + number / val) / 2;
	}while(-1e-4 < val - last && val - last < 1e-4);
	return val;
}

float sqrt_c( float number )
{
	int i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( int * ) &y;     
	i  = 0x5f375a86 - ( i >> 1 ); 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) ); 
	return number*y;
}

float qsqrt(float number)
{
	if(number > 2.0)
		return sqrt_c(number);
	else
		return qsqrt_nt(number); 
}
inline float sqr(float number)
{
	return number * number;
}

void simulate(Position2D& a, Position2D& b, Position2D& c)
{
	// 计算两两之间的距离 
	float distance12 = qsqrt(sqr(x1-x2) + sqr(y1-y2));
    float distance13 = qsqrt(sqr(x1-x3) + sqr(y1-y3));
    float distance23 = qsqrt(sqr(x2-x3) + sqr(y2-y3));
    
    if(distance12 <= 5) distance12 = 7;
    if(distance13 <= 5) distance13 = 7;
    if(distance23 <= 5) distance23 = 7;
    
    // 计算一号球
	float a1_2 = G*m2/sqr(distance12);  // 物体2对物体1的加速度（用上万有引力公式）
    float a1_3 = G*m3/sqr(distance13);  // 物体3对物体1的加速度
    float a1_x = a1_2*(x2-x1)/distance12 + a1_3*(x3-x1)/distance13;  // 物体1受到的水平加速度
    float a1_y = a1_2*(y2-y1)/distance12 + a1_3*(y3-y1)/distance13;  // 物体1受到的垂直加速度
    v1_x = v1_x + a1_x*t;  // 物体1的速度
    v1_y = v1_y + a1_y*t;  // 物体1的速度
    x1 = x1 + v1_x*t;  // 物体1的水平位置
    y1 = y1 + v1_y*t;  // 物体1的垂直位置 
    // 写回
	a.x = x1;
	a.y = y1;
	
	// 计算二号球
	float a2_1 = G*m1/sqr(distance12);
    float a2_3 = G*m3/sqr(distance23);
    float a2_x = a2_1*(x1-x2)/distance12 + a2_3*(x3-x2)/distance23;
    float a2_y = a2_1*(y1-y2)/distance12 + a2_3*(y3-y2)/distance23;
    v2_x = v2_x + a2_x*t;
    v2_y = v2_y + a2_y*t;
    x2 = x2 + v2_x*t;
    y2 = y2 + v2_y*t ;
    b.x = x2;
	b.y = y2;
	
	// 计算三号球
	float a3_1 = G*m1/sqr(distance13);
    float a3_2 = G*m2/sqr(distance23);
    float a3_x = a3_1*(x1-x3)/distance13 + a3_2*(x2-x3)/distance23;
    float a3_y = a3_1*(y1-y3)/distance13 + a3_2*(y2-y3)/distance23;
    v3_x = v3_x + a3_x*t;
    v3_y = v3_y + a3_y*t;
    x3 = x3 + v3_x*t;
    y3 = y3 + v3_y*t;
    c.x = x3;
	c.y = y3;
	
	// 结束 
    
}

void simulate_ex(Position2D& a, Position2D& b, Position2D& c)
{
	for(unsigned int i = 0; i < 10; ++i)
	{
		simulate(a, b, c);
	}
}
