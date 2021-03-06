# Convergence test of the Navier-Stokes solver

Run the cases from the present directory:

```
petibm-navierstokes -directory 20 -options_left -log_view ascii:20/stdout.txt
petibm-navierstokes -directory 60 -options_left -log_view ascii:60/stdout.txt
petibm-navierstokes -directory 180 -options_left -log_view ascii:180/stdout.txt
petibm-navierstokes -directory 540 -options_left -log_view ascii:540/stdout.txt
```

Computes the observed orders of convergence for the velocity components and
the pressure using three consistently refined grids:

```
python scripts/getOrderConvergence.py
```
