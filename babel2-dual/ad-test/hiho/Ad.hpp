#pragma once
namespace hiho {

	double american(double s, double sigma, double k, double r, double t, int simulation);

	void ad00(double s, double sigma, double k, double r, double t, int simulation);
	void ad01(double s, double sigma, double k, double r, double t, int simulation);
	void ad02(double s, double sigma, double k, double r, double t, int simulation);
	void ad03(double s, double sigma, double k, double r, double t, int simulation);

}