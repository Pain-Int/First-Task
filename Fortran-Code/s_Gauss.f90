subroutine s_Gauss(Matrix, RazmerM)
    implicit none

    real, dimension(1:RazmerM,1:RazmerM+1),intent(In):: Matrix
    integer,intent(In):: RazmerM
    integer I, J
    real, dimension(1:RazmerM,1:RazmerM+1):: MatrixAB
    real, dimension(1:RazmerM+1):: Buffer
    real, dimension(1:RazmerM):: moX

    MatrixAB = Matrix

    !приводим к треугольному виду
    do I=1, RazmerM
        if(MatrixAB(I,I) == 0.) then
            Buffer = MatrixAB(I,:)
            MatrixAB(I,:) = MatrixAB(I+1,:)
            MatrixAB(I+1,:) = Buffer
            Buffer = 0
        end if

        do J=I+1, RazmerM
            MatrixAB(J,:) = MatrixAB(J,:) - ( MatrixAB(I,:)*MatrixAB(J,I)/MatrixAB(I,I) )
        end do
    end do

    !обратный ход
    do I = RazmerM, 1, -1
        moX(I) = MatrixAB(I,RazmerM+1)/MatrixAB(I,I)

        do J = RazmerM, I+1, -1
            moX(I) = moX(I) - MatrixAB(I,J)*moX(J)/MatrixAB(I,I)
        end do
    end do

    !call s_WriteMatrix(MatrixAB)

    write(*,*)' '
    write(*,*)'Your answer is'
    write(*,*) moX
    write(*,*)'You can find your answer in Answer.txt'
    open(10, file = 'Answer.txt', status = 'Replace', action = 'write')
    write(10,*) moX

    contains
    !вывод матрицы
    subroutine s_WriteMatrix(Matrix)
        implicit none
        real, dimension(1:RazmerM,1:RazmerM+1):: Matrix
        integer I

        do I=1, RazmerM
            write(*,*) matrix(I, :)
        end do
    end subroutine

end subroutine