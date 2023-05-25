program vecAdd
  
  use omp_lib
  implicit none

  real(kind=8) :: start, finish
  integer :: N=10000000
  real(kind=8), allocatable :: A(:), B(:), C(:)
  integer :: i
  integer :: thread_num 
  integer :: chunk = 16 
  integer :: num_threads = 16

  ! Allocate memory
  allocate( A(N), B(N), C(N))

    ! Initilise data
  do i = 1, N
    A(i) = i*1.0_8
    B(i) = A(i)
  end do

  ! Start timer
  call cpu_time(start)

 thread_num = 0
 !$ call omp_set_num_threads(num_threads)

 !$omp parallel do private(num_threads) & 
 !$omp schedule(dynamic, chunk) 
 do i = 1, N 
     C(i) = A(i) + B(i)
 end do
 !$omp end parallel do   
 
 !$omp parallel do 
 do i = 1, 20
    !$ thread_num = omp_get_thread_num() 
    print *, C(i), "Iteration ", i, "done by thread", thread_num
 end do
 !$omp end parallel do  
 

  call cpu_time(finish)

  ! Print result
  write(*,"(A)")         "------------------------------------"
  write(*,"(A,F10.3)")   "runtime:  ", finish-start
  write(*,"(A)")         "------------------------------------"

  deallocate(A,B, C)
end program vecAdd



