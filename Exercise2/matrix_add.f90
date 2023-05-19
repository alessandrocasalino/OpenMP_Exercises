program vecAdd
    use omp_lib

    implicit none
    real(kind=8) :: time1, time2
    integer :: M = 10000, N =10000
    real(kind=8), allocatable :: A(:,:), B(:,:), C(:,:)
    integer :: i,j

    ! Allocate memory
    allocate( A(N,N), B(N,N), C(N,N))

    ! Initilise data

    do i = 1, M
        do j = 1, N
            A(i,j) = 2.0_8
            B(i,j) = 2.0_8
        end do
    end do

    ! Start timer
    time1 = omp_get_wtime()
    do i = 1, M
        do j = 1, N
            C(i,j) = A(i,j) * B(i,j)
        end do
    end do
    time2 = omp_get_wtime() - time1

    do, i=1,4
    write(*,*) ( C(i,j), j=1,4 )
    enddo

    ! Print result
    write(*,"(A)")         "------------------------------------"
    write(*,"(A,F10.3)")   "runtime:  ", time2
    write(*,"(A)")         "------------------------------------"

    deallocate(A,B, C)
end program vecAdd
