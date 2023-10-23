#pragma once

#ifndef FLATVECTOR_H
#define FLATVECTOR_H
#include "Common.h"
//Just a vector
class FlatVector
{
public:
	float x; // Tọa độ x
	float y; // Tọa độ y

	FlatVector() :
		x(0), y(0)
	{}

	FlatVector(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	// So sánh (Compare)
	bool Equal(FlatVector v)
	{
		return this->x == v.x && this->y == v.y;
	}
	FlatVector operator+ (const FlatVector& v1)
	{
		FlatVector tmp(this->x + v1.x, this->y + v1.y);
		return tmp;
	}
	FlatVector operator- (const FlatVector& v1)
	{
		FlatVector tmp(this->x - v1.x, this->y - v1.y);
		return tmp;
	}
	FlatVector operator* (float s)
	{
		FlatVector tmp(this->x * s, this->y * s);
		return tmp;
	}
	FlatVector operator/ (float s)
	{
		FlatVector tmp(this->x / s, this->y / s);
		return tmp;
	}
	//Các công thức toán 

	//Độ dài vector từ tọa độ
	float Length()
	{
		return std::sqrt(x * x + y * y);
	}
	//Độ dài vector
	float Distance(FlatVector b)
	{
		float dx = x - b.x;
		float dy = y - b.y;
		return std::sqrt(dx * dx + dy * dy);
	}
	// vector đơn vị
	FlatVector Normalize()
	{
		FlatVector tmp(x / Length(), y / Length());
		return tmp;
	}
	//Tích vô hướng
	float Dot(FlatVector b)
	{
		return x * b.x + y * b.y;
	}
	//Tích có hướng
	float Cross(FlatVector b)
	{
		return x * b.y - y * b.x;
	}

	//Chuyển đổi tọa độ quay xung quanh điểm chính giữa:
	// v là vector cần được chuyển đổi
	// center là vị trí ở giữa
	// angle là góc quay
	// return về 1 FlatVector
	FlatVector Transform(FlatVector center, float angle)
	{
		//x1 s= x0cos(angle) – y0sin(angle)
		//y1 = x0sin(angle) + y0cos(angle)
		//float x1 = v.x * std::cos(angle) - v.y * std::sin(angle) + center.x;
		//float y1 = v.x * std::sin(angle) + v.y * std::cos(angle) + center.y;
		//convert angle from degrees to radians
		angle = angle * M_PI / 180;
		FlatVector tmp(((x - center.x) * std::cos(angle) - (y - center.y) * std::sin(angle)) + center.x
			, (x - center.x) * std::sin(angle) + (y - center.y) * std::cos(angle) + center.y);
		return tmp;
	}
};

#endif // !FLATVECTOR_H





