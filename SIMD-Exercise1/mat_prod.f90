program mat_prod

    use omp_lib

    implicit none
    real(kind=8) :: time1, time2
    integer :: n = 1000;
    real(kind(1.d0)), dimension(:,:), allocatable :: a, b, c
    integer :: i, j, k

    !.............Allocate memory.............
    allocate(a(n,n),b(n,n),c(n,n))

    !.............Initilization.............
    call random_number(a)
    call random_number(b)


    ! Start timer
    ! call cpu_time(start)

    time1 = omp_get_wtime();

    do j=1, n
        do k=1, n
            do i=1, n
                c(i,j) = c(i,j) + a(i,k)*b(k,j)
            end do
        end do
    end do


    time2 = omp_get_wtime() - time1;

    ! call cpu_time(finish)

    do, i=1,4
    write(*,*) ( c(i,j), j=1,4 )
    enddo

    ! Print result
    write(*,"(A)")         "------------------------------------"
    ! write(*,"(A,F10.3)")   "runtime:  ", finish-start
    write(*,"(A,F10.3)")   "runtime:  ", time2
    write(*,"(A)")         "------------------------------------"

    deallocate(A,B, C)
end program mat_prod
