subroutine s_Seidel(Matrix, RazmerM, n)
    use m_MyMatrixLyb
    implicit none

    real, dimension(1:RazmerM,1:RazmerM+1),intent(In):: Matrix
    integer,intent(In):: RazmerM
    real, intent(In):: n
    integer I, J, Hvatit
    real, dimension(1:RazmerM,1:4):: MatrixAB, MatrixA
    real, dimension(1:RazmerM):: moX, moXNew
    real del
    integer A

    MatrixAB = Matrix

    !call s_WriteMatrix(MatrixAB)

    !заполняем матрицу новыми коэфициентами
    !переносим лишнее вправо, делим на главный элемент
    do I=1, RazmerM
    
        MatrixA(I,RazmerM+1) = MatrixAB(I,RazmerM+1)/MatrixAB(I,I)
        do J=1, RazmerM
            if (I /= J) then
                MatrixA(I,J) = -MatrixAB(I,J)/MatrixAB(I,I)
            else
                MatrixA(I,J) = 0
            end if
        end do
    end do

    moX = MatrixAB(:,RazmerM+1)
    moXNew = moX

    !считаем Х
    A = 0

    do
        A = A+1
        Hvatit = 0
        do I=1, RazmerM
            moXNew(I) = sum(MatrixA(I,1:RazmerM)*moX) + MatrixA(I,RazmerM+1)
            
            del = abs(( moXNew(I) - moX(I) )/moX(I))
            
            if (del >= n) then
                Hvatit = Hvatit+1
            end if

            moX = moXNew
        end do

        if (Hvatit == 0) then
            exit
        end if
    end do

    !вывод
    write(*,*)' '
    write(*,*)'Your answer is'
    write(*,*) moX
    write(*,*)'You can find your answer in Answer.txt'
    open(10, file = 'Answer.txt', status = 'Replace', action = 'Write')
    write(10,*) moX
    write(*,*) 'Iteraciy = ', A

    contains
    !вывод матрицы
    subroutine s_WriteMatrix(Matrix)
        implicit none
        real, dimension(1:RazmerM,1:RazmerM+1):: Matrix
        integer I

        do I=1, RazmerM
            write(*,*) Matrix(I, :)
        end do

        write(*,*)' '
    end subroutine

end subroutine