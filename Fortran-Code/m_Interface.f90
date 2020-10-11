module m_Interface
    implicit none

    interface
        subroutine s_Gauss(Matrix, RazmerM)
            integer,intent(In):: RazmerM
            real, dimension(1:RazmerM,1:RazmerM+1),intent(In):: Matrix
        end subroutine

        subroutine s_Progonka(Matrix, RazmerM)
            integer,intent(In):: RazmerM
            real, dimension(1:RazmerM,1:RazmerM+1),intent(In):: Matrix
        end subroutine

        subroutine s_Seidel(Matrix, RazmerM, n)
            integer,intent(In):: RazmerM
            real, dimension(1:RazmerM,1:RazmerM+1),intent(In):: Matrix
            real, intent(In):: n
        end subroutine
    end interface

    contains

    function f_ReadMatrix(NameOfFile, Razmer)
        character(20), intent(In):: NameOfFile
        integer, intent(In):: Razmer
        real, dimension(1:Razmer,1:Razmer+1):: f_ReadMatrix
        integer I

        open(1, file = trim(NameOfFile)//'.txt', status = 'Old', action = 'read')
        !читаем матрицу
        do I=1, Razmer
            read(1,*) f_ReadMatrix(I, 1:Razmer+1)
        end do
    end function
end module