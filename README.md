# 42_Philosophers

## Test cases

#### A philo should die
```
./philo 1 800 200 200 # shouldn't even eat
./philo 4 310 200 100
./philo 2 310 200 100
./philo 4 310 200 100
./philo 2 60 60 60
```

#### Simulation should stop after each philo has eaten at least x times
```
./philo 5 800 200 200 7
./philo 4 800 200 200 10
```

#### Simulation should run indefinitely
```
./philo 4 410 200 200
./philo 4 800 200 200
./philo 5 800 200 200
```
## Check for data races, correct mutex (un)locking and leaks
```
valgrind --tool=helgrind # add --fairsched=yes option if taking too long to run
valgrind --tool=drd # add --fairsched=yes option if taking too long to run
-fsanitize=thread # compile with
```