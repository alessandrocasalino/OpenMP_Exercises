program pi_main
    use omp_lib
    implicit none
    real(kind=8) :: time1, time2

    ! Local variables
    integer, parameter :: num_steps = 100000000
    real(kind=8) :: step                           ! the step size
    integer      :: ii                             ! genereric counter
    real(kind=8) :: x, x2                          ! intermediate value
    real(kind=8) :: pi = 0.0_8                     ! overall estimate
    real(kind=8) :: sum = 0.0_8                    ! variable to store partial sum

    real(kind=8), parameter :: PI_8 = 4.0_8 * atan(1.0_8)

    ! step size is dependent upon the number of steps
    step = 1.0_8/num_steps

    ! Start timer
    time1 = omp_get_wtime()

    ! Main loop
    !$omp parallel do private(x) reduction(+:sum)
    do ii = 1, num_steps
        x = (ii-0.5_8)*step
        x2 = 4.0_8/(1.0_8+x*x)
        sum = sum + x2
    end do
    !$omp end parallel do

    pi = step * sum

    ! Stop timer
    time2 = omp_get_wtime() - time1;

    ! Print result
    write(*,"(A)")         "------------------------------------"
    write(*,"(A,F19.16)") "pi is:    ", pi
    write(*,"(A,F19.16)") "error is: ", abs(pi - PI_8)
    write(*,"(A,F10.3)")   "runtime:  ", time2
    write(*,"(A)")         "------------------------------------"
end program pi_main! Parallelize this block of code
