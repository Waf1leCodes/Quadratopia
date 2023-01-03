#pragma once
#include "pch.h"
#include "debug.h"

using std::floor, std::ceil, std::round, std::abs, std::min, std::max;

inline Vector2 operator + (Vector2 const &v1, Vector2 const &v2) { 
    Vector2 v{v1.x + v2.x, v1.y + v2.y}; 
    return v;
}

inline Vector2 operator - (Vector2 const &v1, Vector2 const &v2) { 
    Vector2 v{v1.x - v2.x, v1.y - v2.y}; 
    return v;
} 

inline Vector2 operator * (Vector2 const &v1, Vector2 const &v2) { 
    Vector2 v{v1.x * v2.x, v1.y * v2.y}; 
    return v; 
} 

inline Vector2 operator / (Vector2 const &v1, Vector2 const &v2) { 
    Vector2 v{v1.x / v2.x, v1.y / v2.y}; 
    return v;
}

inline Color ColorFade(Color const &c1, Color const &c2, float fraction) {
    return Color {
        (unsigned char) (float(c1.r) + (float(c2.r) - float(c1.r)) * fraction),
        (unsigned char) (float(c1.g) + (float(c2.g) - float(c1.g)) * fraction),
        (unsigned char) (float(c1.b) + (float(c2.b) - float(c1.b)) * fraction),
        (unsigned char) (float(c1.a) + (float(c2.a) - float(c1.a)) * fraction),
    };
}