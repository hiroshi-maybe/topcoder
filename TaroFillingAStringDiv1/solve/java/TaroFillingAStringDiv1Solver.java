import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class TaroFillingAStringDiv1Solver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        int N = (Integer) reader.next(Integer.class);
        reader.next();
        
        List<Integer> positionBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] position = new int[positionBoxed.size()];
        for (int _i = 0; _i < positionBoxed.size(); ++_i)
            position[_i] = positionBoxed.get(_i);
        reader.next();
        
        String value = (String) reader.next(String.class);
        reader.close();

        TaroFillingAStringDiv1 solver = new TaroFillingAStringDiv1();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.getNumber(N, position, value));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
