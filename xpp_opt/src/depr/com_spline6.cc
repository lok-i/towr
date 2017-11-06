/**
@file    com_spline6.cc
@author  Alexander W. Winkler (winklera@ethz.ch)
@date    Oct 21, 2015
@brief   Defines ComSpline6, which realizes a ComSpline
 */

#include <xpp/opt/depr/com_spline6.h>

#include <cmath>
#include <stddef.h>
#include <Eigen/Sparse>

#include <xpp/opt/polynomial.h>

namespace xpp {
namespace opt {

ComSpline6::ComSpline6 ()
{
  // TODO Auto-generated constructor stub
}

ComSpline6::~ComSpline6 ()
{
  // TODO Auto-generated destructor stub
}

//ComSpline6::Derivatives
//ComSpline6::GetInitialFreeMotions () const
//{
//  return {kPos, kVel};
//}
//
//ComSpline6::Derivatives
//ComSpline6::GetJunctionFreeMotions () const
//{
//  return {kPos, kVel/*, kAcc*/};
//}

//void
//ComSpline6::SetSplineXYCoefficients (const VectorXd& optimized_coeff)
//{
//  CheckIfSplinesInitialized();
//
//  for (size_t p=0; p<polynomials_.size(); ++p)
//    for (const Coords3D dim : {X,Y})
//      for (auto c : Polynomial::AllSplineCoeff)
//        polynomials_.at(p).SetCoefficients(dim, c, optimized_coeff[Index(p,dim,c)]);
//}

void
ComSpline6::GetJacobianPos (double t_poly, int id, Coords3D dim, JacobianRow& jac) const
{
  // x_pos = at5 +   bt4 +  ct3 + dt*2 + et + f
  jac.insert(Index(id,dim,PolyCoeff::A))   = std::pow(t_poly,5);
  jac.insert(Index(id,dim,PolyCoeff::B))   = std::pow(t_poly,4);
  jac.insert(Index(id,dim,PolyCoeff::C))   = std::pow(t_poly,3);
  jac.insert(Index(id,dim,PolyCoeff::D))   = std::pow(t_poly,2);
  jac.insert(Index(id,dim,PolyCoeff::E))   = t_poly;
  jac.insert(Index(id,dim,PolyCoeff::F))   = 1;
}

void
ComSpline6::GetJacobianVel (double t_poly, int id, Coords3D dim, JacobianRow& jac) const
{
  // x_vel = 5at4 +   4bt3 +  3ct2 + 2dt + e
  jac.insert(Index(id,dim,PolyCoeff::A))   = 5 * std::pow(t_poly,4);
  jac.insert(Index(id,dim,PolyCoeff::B))   = 4 * std::pow(t_poly,3);
  jac.insert(Index(id,dim,PolyCoeff::C))   = 3 * std::pow(t_poly,2);
  jac.insert(Index(id,dim,PolyCoeff::D))   = 2 * t_poly;
  jac.insert(Index(id,dim,PolyCoeff::E))   = 1;
}

void
ComSpline6::GetJacobianAcc (double t_poly, int id, Coords3D dim, JacobianRow& jac) const
{
  // x_acc = 20at3 + 12bt2 + 6ct   + 2d
  jac.insert(Index(id,dim,PolyCoeff::A))   = 20.0 * std::pow(t_poly,3);
  jac.insert(Index(id,dim,PolyCoeff::B))   = 12.0 * std::pow(t_poly,2);
  jac.insert(Index(id,dim,PolyCoeff::C))   =  6.0 * t_poly;
  jac.insert(Index(id,dim,PolyCoeff::D))   =  2.0;
}

void
ComSpline6::GetJacobianJerk (double t_poly, int id, Coords3D dim, JacobianRow& jac) const
{
  // x_jerk = 60at2 +   24bt +  6c
  jac.insert(Index(id,dim,PolyCoeff::A))   = 60 * std::pow(t_poly,2);
  jac.insert(Index(id,dim,PolyCoeff::B))   = 24 * std::pow(t_poly,1);
  jac.insert(Index(id,dim,PolyCoeff::C))   = 6;
}

//void
//ComSpline6::GetJacobianVelSquaredImpl (double t_poly, int id, Coords3D dim,
//                                       JacobianRow& jac) const
//{
//  double a = polynomials_.at(id).GetCoefficient(dim,PolyCoeff::A);
//  double b = polynomials_.at(id).GetCoefficient(dim,PolyCoeff::B);
//  double c = polynomials_.at(id).GetCoefficient(dim,PolyCoeff::C);
//  double d = polynomials_.at(id).GetCoefficient(dim,PolyCoeff::D);
//  double e = polynomials_.at(id).GetCoefficient(dim,PolyCoeff::E);
//
//  double t1 = t_poly;
//  double t2 = t1*t1;
//  double t3 = t2*t1;
//  double t4 = t3*t1;
//
//  double k1 = 5*a*t4 + 4*b*t3 + 3*c*t2 + 2*d*t1 + e;
//
//  // generated with matlab (com_motion_derivatives.m)
//  jac.insert(Index(id,dim,PolyCoeff::A)) = 10*t4*k1;
//  jac.insert(Index(id,dim,PolyCoeff::B)) =  8*t3*k1;
//  jac.insert(Index(id,dim,PolyCoeff::C)) =  6*t2*k1;
//  jac.insert(Index(id,dim,PolyCoeff::D)) =  4*t1*k1;
//  jac.insert(Index(id,dim,PolyCoeff::E)) =  2*1 *k1;
//  jac.insert(Index(id,dim,PolyCoeff::F)) =  0;
//}
//
//void
//ComSpline6::GetJacobianPosVelSquaredImpl (double t_poly, int id, Coords3D dim,
//                                          JacobianRow& jac) const
//{
//  double a = polynomials_.at(id).GetCoefficient(dim,PolyCoeff::A);
//  double b = polynomials_.at(id).GetCoefficient(dim,PolyCoeff::B);
//  double c = polynomials_.at(id).GetCoefficient(dim,PolyCoeff::C);
//  double d = polynomials_.at(id).GetCoefficient(dim,PolyCoeff::D);
//  double e = polynomials_.at(id).GetCoefficient(dim,PolyCoeff::E);
//  double f = polynomials_.at(id).GetCoefficient(dim,PolyCoeff::F);
//
//  double t1 = t_poly;
//  double t2 = t1*t1;
//  double t3 = t2*t1;
//  double t4 = t3*t1;
//  double t5 = t4*t1;
//
//  double k1 = 5*a*t4 + 4*b*t3 + 3*c*t2 + 2*d*t1 + e;
//
//  // generated with matlab (com_motion_derivatives.m)
//  jac.insert(Index(id,dim,PolyCoeff::A)) = t4*k1*(15*a*t5 + 14*b*t4 + 13*c*t3 + 12*d*t2 + 11*e*t1 + 10*f);
//  jac.insert(Index(id,dim,PolyCoeff::B)) = t3*k1*(13*a*t5 + 12*b*t4 + 11*c*t3 + 10*d*t2 +  9*e*t1 +  8*f);
//  jac.insert(Index(id,dim,PolyCoeff::C)) = t2*k1*(11*a*t5 + 10*b*t4 +  9*c*t3 +  8*d*t2 +  7*e*t1 +  6*f);
//  jac.insert(Index(id,dim,PolyCoeff::D)) = t1*k1* (9*a*t5 +  8*b*t4 +  7*c*t3 +  6*d*t2 +  5*e*t1 +  4*f);
//  jac.insert(Index(id,dim,PolyCoeff::E)) = 1 *k1* (7*a*t5 +  6*b*t4 +  5*c*t3 +  4*d*t2 +  3*e*t1 +  2*f);
//  jac.insert(Index(id,dim,PolyCoeff::F)) =    k1*k1;
//}

} // namespace opt
} // namespace xpp