/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef VALUERANGEMARKER_H
#define VALUERANGEMARKER_H

#include "QuadraturePointMarker.h"

// libmesh includes
#include "libmesh/mesh_tools.h"

class ValueRangeMarker;

template<>
InputParameters validParams<ValueRangeMarker>();

class ValueRangeMarker : public QuadraturePointMarker
{
public:
  ValueRangeMarker(const std::string & name, InputParameters parameters);
  virtual ~ValueRangeMarker(){};

protected:
  virtual MarkerValue computeQpMarker();

  Real _lower_bound;
  Real _upper_bound;
  Real _buffer_size;

  MarkerValue _third_state;
  MarkerValue _inside;
  MarkerValue _outside;

  VariableValue & _u;
};

#endif /* VALUERANGEMARKER_H */
