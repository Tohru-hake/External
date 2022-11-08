#pragma once
#include <numbers>
#include <cmath>
#include <d3d9.h>
#include <d3dx9.h>
#include <intrin.h>
#include <corecrt_math_defines.h>

struct Vector3
{
	// constructor
	constexpr Vector3(
		const float x = 0.f,
		const float y = 0.f,
		const float z = 0.f) noexcept :
		x(x), y(y), z(z) { }

	// operator overloads
	constexpr const Vector3 operator-(const Vector3& other) const noexcept
	{
		return Vector3{ x - other.x, y - other.y, z - other.z };
	}

	constexpr const Vector3 operator+(const Vector3& other) const noexcept
	{
		return Vector3{ x + other.x, y + other.y, z + other.z };
	}

	constexpr const Vector3 operator/(const float factor) const noexcept
	{
		return Vector3{ x / factor, y / factor, z / factor };
	}

	constexpr const Vector3 operator*(const float factor) const noexcept
	{
		return Vector3{ x * factor, y * factor, z * factor };
	}

	// utils
	constexpr const Vector3 ToAngle() const noexcept
	{
		return Vector3{
			std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
			std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
			0.0f };
	}

	constexpr const bool IsZero() const noexcept
	{
		return x == 0.f && y == 0.f && z == 0.f;
	}

	// struct data
	float x, y, z;
};

struct Vector2
{
	float x = { }, y = { };

	// operator overloads
	constexpr const Vector2 operator-(const Vector2& other) const noexcept
	{
		return Vector2{ x - other.x, y - other.y };
	}

	constexpr const Vector2 operator+(const Vector2& other) const noexcept
	{
		return Vector2{ x + other.x, y + other.y };
	}

	constexpr const Vector2 operator/(const float factor) const noexcept
	{
		return Vector2{ x / factor, y / factor };
	}

	constexpr const Vector2 operator*(const float factor) const noexcept
	{
		return Vector2{ x * factor, y * factor };
	}
};

#define Matrix D3DXMATRIX