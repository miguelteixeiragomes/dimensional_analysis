#include "test_cuda.cuh"

__global__ void cuda_dims() {
	int32<Time> a(5);
	int32<Time> b(6);
	int64<> c(7);
	int64<> d(8);
	float32<> e(3.14f);
	float64<> f(2.7);
	e = f;
	a + b;
	
	pow<7>(pow<1, 7>(float32<Time>(7.2487)));
	float32<Length>(5) + sqrtf(float32<Area>(25));
	float64<Length>(5) + cbrt(float64<Volume>(125));
	
	float64<Velocity> lightspeed = 1.0 / sqrt(float64<Permittivity>(8.85418781762039e-12) * float64<Permeability>(1.256637061435917e-6));
}

void test_cuda() {
	cuda_dims<<<2, 2>>>();
}