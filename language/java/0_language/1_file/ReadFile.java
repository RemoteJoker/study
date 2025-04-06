import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ReadFile {
    public static void main(String[] args) {
        String filePath = "test.txt";
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line); // 处理每一行
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

// 大文本文件逐行读取	BufferedReader
// 快速读取小文本文件	Files.readAllLines/readString
// 按分隔符读取（如CSV）	Scanner
// 二进制文件	FileInputStream
// Java 8+ 流式处理	Files.lines()