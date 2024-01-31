
template <typename T>
double scalar_difference (T x, T y)
{
    return (abs(x.getScalarValue() - y.getScalarValue()));
}

template <typename T>
bool equals (T x, T y)
{
    return (x == y);
}