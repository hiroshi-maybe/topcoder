import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class FilipTheFrogSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        List<Integer> positionsBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] positions = new int[positionsBoxed.size()];
        for (int _i = 0; _i < positionsBoxed.size(); ++_i)
            positions[_i] = positionsBoxed.get(_i);
        reader.next();
        
        int L = (Integer) reader.next(Integer.class);
        reader.close();

        FilipTheFrog solver = new FilipTheFrog();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.countReachableIslands(positions, L));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
