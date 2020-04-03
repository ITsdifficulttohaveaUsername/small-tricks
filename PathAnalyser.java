//assignment for discipline:Designation Of Network Program.2020/3/26.

//Program function:User give the absolute path of a document,which type is String,and this program will return all the files
//and documents contained by the document user have already given.

//I use recursion to finish the function.

package PathAnalyser;
import java.io.File;

public class PathAnalyser{
    public String path;

    //I write two constructors.The lower constructor is not necessary.I write it just because my habit.
    public PathAnalyser(String path){
        this.path = path;
    }
    public PathAnalyser(){

    }

    //This function is using to cooperate with constructor2.
    public void getpath(String path){
        this.path = path;
    }

    //this function is essential part of program.
    public int pathanalyse(String path){
        File filepath = new File(path);
        //By this step,I can get all the files and documents' name this path document contain.
        String[] list = filepath.list();
        //A circulation to recursive scan all the files and documents.
        for(int i = 0;i < list.length;i++){
            //elements in list is name of files and documents,not the absolute path.So we have to attach name to variable
            // 'path' to get the absolute path.
            String nextpath = path + "\\"+list[i];
            File testpath = new File(nextpath);
            //if this absolute path represents a file,we will output its name.However,if it represents a document,just
            //recursion.
            if(testpath.isDirectory()){
                pathanalyse(nextpath);
            }
            else{
                System.out.println(testpath.getAbsolutePath());
            }
        }
        System.out.println(path);
        return 0;
    }
}
