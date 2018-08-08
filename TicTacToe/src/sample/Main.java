package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public class Main extends Application {

    public static char whoseturn='X';
    public static Label lblstatus= new Label("X's Turn!");
    private static Cell[][] cells=new Cell[3][3];

    public static boolean isWon(char ch){
        for (int i=0;i<3;i++){
            if (cells[i][0].getToken()==whoseturn && cells[i][1].getToken()==whoseturn && cells[i][2].getToken()==whoseturn) return true;
            if (cells[0][i].getToken()==whoseturn && cells[1][i].getToken()==whoseturn && cells[2][i].getToken()==whoseturn) return true;
            if (cells[0][0].getToken()==whoseturn && cells[1][1].getToken()==whoseturn && cells[2][2].getToken()==whoseturn) return true;
            if (cells[0][2].getToken()==whoseturn && cells[1][1].getToken()==whoseturn && cells[2][0].getToken()==whoseturn) return true;
        }

        return false;
    }

    public static boolean isFull(){
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                if (cells[i][j].getToken()==' '){
                    return false;
                }
            }
        }

        return true;
    }

    @Override
    public void start(Stage primaryStage) throws Exception{
        GridPane pane=new GridPane();
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                pane.add(cells[i][j]=new Cell(),j,i);
            }
        }

        BorderPane borderPane=new BorderPane();
        borderPane.setCenter(pane);
        borderPane.setBottom(lblstatus);



        //Parent root = FXMLLoader.load(getClass().getResource("sample.fxml"));
        Scene scene=new Scene(borderPane, 400, 400);
        primaryStage.setTitle("Hello World");
        primaryStage.setScene(scene);
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
