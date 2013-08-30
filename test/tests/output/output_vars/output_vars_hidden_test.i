[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  xmax = 1
  ymin = 0
  ymax = 1
  nx = 10
  ny = 10
  elem_type = QUAD9
  # This test doesn't work in parallel with ParallelMesh because writing
  # CONSTANT MONOMIAL data doesn't currently work. See #2122.
  distribution = serial
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]

  [./v]
    order = SECOND
    family = LAGRANGE
  [../]

  # ODE variables
  [./x]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  [../]
  [./y]
    family = SCALAR
    order = FIRST
    initial_condition = 2
  [../]
[]

[AuxVariables]
  [./elemental]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./elemental_restricted]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./nodal]
    order = FIRST
    family = LAGRANGE
  [../]

  [./nodal_restricted]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./td]
    type = TimeDerivative
    variable = u
  [../]

  [./diff_u]
    type = Diffusion
    variable = u
  [../]

  [./conv_u]
    type = CoupledForce
    variable = u
    v = v
  [../]

  [./diff_v]
    type = Diffusion
    variable = v
  [../]
[]

[AuxKernels]
  [./elemental]
    type = ConstantAux
    variable = elemental
    value = 1
  [../]

  [./elemental_restricted]
    type = ConstantAux
    variable = elemental_restricted
    value = 1
  [../]

  [./nodal]
    type = ConstantAux
    variable = elemental
    value = 2
  [../]

  [./nodal_restricted]
    type = ConstantAux
    variable = elemental_restricted
    value = 2
  [../]
[]

[ScalarKernels]
  [./td1]
    type = ODETimeDerivative
    variable = x
  [../]
  [./ode1]
    type = ImplicitODEx
    variable = x
    y = y
  [../]

  [./td2]
    type = ODETimeDerivative
    variable = y
  [../]
  [./ode2]
    type = ImplicitODEy
    variable = y
    x = x
  [../]
[]

[BCs]
  active = 'left_u right_u left_v'

  [./left_u]
    type = DirichletBC
    variable = u
    boundary = 1
    value = 1
  [../]

  [./right_u]
    type = DirichletBC
    variable = u
    boundary = 3
    value = 9
  [../]

  [./left_v]
    type = DirichletBC
    variable = v
    boundary = 1
    value = 5
  [../]

  [./right_v]
    type = DirichletBC
    variable = v
    boundary = 2
    value = 2
  [../]
[]

[Postprocessors]
  [./x]
    type = ScalarVariable
    variable = x
    execute_on = timestep
  [../]
  [./y]
    type = ScalarVariable
    variable = y
    execute_on = timestep
  [../]
[]

[Executioner]
  type = Transient

  #Preconditioned JFNK (default)
  solve_type = 'PJFNK'


  dt = 0.01
  num_steps = 10
[]

[Output]
  file_base = out_hidden
  output_initial = true
  interval = 1
  exodus = true
  perf_log = true
  hidden_variables = 'u elemental nodal x'
[]
