subroutine s_Progonka(Matrix, RazmerM)
    implicit none

    real, dimension(1:RazmerM,1:RazmerM+1),intent(In):: Matrix
    integer,intent(In):: RazmerM
    integer I
    real, dimension(1:RazmerM,1:4):: MatrixAB
    real, dimension(1:RazmerM):: moX, Alpha, Beta
    real, dimension(1:RazmerM+1):: Buffer

    !делаем красиво
    do I=1, RazmerM
        Buffer = Matrix(I,:)
    
        MatrixAB(I,1:3) = Buffer(I-1:I+1)
        MatrixAB(I,4) = Buffer(RazmerM+1)
    end do

    MatrixAB(1,1) = 0
    MatrixAB(RazmerM,3) = 0

    !Call s_WriteMatrix(MatrixAB)

    !прямой ход
    Alpha = 0
    Beta = 0
    moX=0

    do I=1, RazmerM-1
        Alpha(I+1) = -MatrixAB(I,3)/(MatrixAB(I,1)*Alpha(I)+MatrixAB(I,2))
        Beta(I+1) = (MatrixAB(I,4)-MatrixAB(I,1)*Beta(I))/(MatrixAB(I,1)*Alpha(I)+MatrixAB(I,2))
    end do

    !обратный ход
    moX(RazmerM) = (MatrixAB(RazmerM,4)-MatrixAB(RazmerM,1)*Beta(RazmerM))/(MatrixAB(RazmerM,2)+MatrixAB(RazmerM,1)*Alpha(RazmerM))
    do I = RazmerM-1, 1, -1
        moX(I) = Alpha(I+1)*moX(I+1)+Beta(I+1)
    end do

    !вывод
    write(*,*)' '
    write(*,*)'Your answer is'
    write(*,*) moX
    write(*,*)'You can find your answer in Answer.txt'
    open(10, file = 'Answer.txt', status = 'Replace', action = 'Write')
    write(10,*) moX

    contains
    !вывод матрицы
    subroutine s_WriteMatrix(Matrix)
        implicit none
        real, dimension(1:RazmerM,1:4):: Matrix
        integer I

        write(*,*)'  Alpha            Beta             Gamma            Delta'
        do I=1, RazmerM
            write(*,*) matrix(I,:)
        end do
    end subroutine

end subroutine