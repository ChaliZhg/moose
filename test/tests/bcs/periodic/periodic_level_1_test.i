[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 4
  ny = 4
  nz = 0
  xmax = 40
  ymax = 40
  zmax = 0
  elem_type = QUAD4
  uniform_refine = 4
[]

[Variables]
  active = 'u'

  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  active = 'diff conv forcing dot'

  [./diff]
    type = CoefDiffusion
    variable = u
    coef = 1e-5
  [../]

  [./conv]
    type = Convection
    variable = u
    velocity = '-0.4 0 0'
  [../]

  [./forcing]
    type = GaussContForcing
    variable = u
    x_center = 8.0
    y_center = 18.0
    x_spread = 1.0
    y_spread = 5.0
  [../]

  [./dot]
    type = TimeDerivative
    variable = u
  [../]
[]

[BCs]

  [./Periodic]
    [./x]
      variable = u
      primary = 3
      secondary = 1
      translation = '40 0 0'
    [../]

    [./y]
      variable = u
      primary = 0
      secondary = 2
      translation = '0 40 0'
    [../]
  [../]
[]

[Executioner]
  type = Transient
  dt = 2
  num_steps = 10
  nl_rel_tol = 1e-10

  [./Adaptivity]
    refine_fraction = .80
    coarsen_fraction = .02
    max_h_level = 4
    error_estimator = KellyErrorEstimator
  [../]
  nl_rel_tol = 1e-12
[]

[Output]
  file_base = level1
  interval = 1
  exodus = true
  perf_log = true
[]

