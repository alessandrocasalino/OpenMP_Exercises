program saxpy
 use omp_lib

 implicit none
 integer :: i, N, chunk 
 real(kind=8), allocatable :: x(:), y(:)
 real :: a,start_time, end_time
 a = 2.0d0
 N = 1e8
 chunk  = 16
 
 allocate(x(n),y(n))

! Parallelize this block of code (optional) 
 do i = 1, N
  x = 1.0d0
  y = 2.0d0
 end do 
 
 call cpu_time(start_time)
 !$omp parallel do schedule(static, chunk)
 do i = 1, N
  y(i) = y(i) + a * x(i) 
 end do
 !$omp end parallel do 
 call cpu_time(end_time)
 deallocate(x,y)

 print '(a,f8.6)', 'SAXPY Time: ', end_time - start_time

end program saxpy


