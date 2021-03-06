/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "DomainIntegralTopologicalQFunction.h"

template<>
InputParameters validParams<DomainIntegralTopologicalQFunction>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<unsigned int>("ring_index", "The ring of elements that defines the integration domain");
  params.addRequiredParam<UserObjectName>("crack_front_definition","The CrackFrontDefinition user object name");
  params.addParam<unsigned int>("crack_front_point_index","The index of the point on the crack front corresponding to this q function");
  params.set<bool>("use_displaced_mesh") = false;
  return params;
}

DomainIntegralTopologicalQFunction::DomainIntegralTopologicalQFunction(const std::string & name, InputParameters parameters):
    AuxKernel(name, parameters),
    _ring_number(getParam<unsigned int>("ring_index")),
    _crack_front_definition(&getUserObject<CrackFrontDefinition>("crack_front_definition")),
    _has_crack_front_point_index(isParamValid("crack_front_point_index")),
    _crack_front_point_index(_has_crack_front_point_index ? getParam<unsigned int>("crack_front_point_index") : 0),
    _treat_as_2d(false)
{}

void
DomainIntegralTopologicalQFunction::initialSetup()
{
  _treat_as_2d = _crack_front_definition->treatAs2D();

  if (_treat_as_2d)
  {
    if (_has_crack_front_point_index)
    {
      mooseWarning("crack_front_point_index ignored because CrackFrontDefinition is set to treat as 2D");
    }
  }
  else
  {
    if (!_has_crack_front_point_index)
    {
      mooseError("crack_front_point_index must be specified in DomainIntegralTopologicalQFunction");
    }
  }
}

Real
DomainIntegralTopologicalQFunction::computeValue()
{

  Real q = 0;
  bool is_node_in_ring = _crack_front_definition->isNodeInRing(_ring_number,_current_node->id(),_crack_front_point_index);
  if (is_node_in_ring)
    q = 1;

  return q;
}
