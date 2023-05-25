program saxpy

 implicit none
 integer :: i,n 
 real,dimension(:), allocatable :: x, y 
 real :: a,start_time, end_time
 a = 2.0d0 
 n=256*512*512
 allocate(x(n),y(n))

! Parallelize this block of code (optional) 
 do i = 1, n
  x = 1.0d0
  y = 2.0d0
 end do 
 
 call cpu_time(start_time)
 !$omp parallel do default(shared) private(i)
 do i = 1, n
  y(i) = y(i) + a * x(i) 
 end do
 !$omp end parallel do
 call cpu_time(end_time)

 print '(a,f8.6)', 'SAXPY Time: ', end_time - start_time
 
 do i = 1, 5
   print *, y(i)
 end do 

deallocate(x,y)
end program saxpy


