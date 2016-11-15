import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class GridSortMaxSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        int n = (Integer) reader.next(Integer.class);
        reader.next();
        
        int m = (Integer) reader.next(Integer.class);
        reader.next();
        
        List<Integer> gridBoxed = (List<Integer>) reader.next(new TypeRef<List<Integer>>(){}.getType());
        int[] grid = new int[gridBoxed.size()];
        for (int _i = 0; _i < gridBoxed.size(); ++_i)
            grid[_i] = gridBoxed.get(_i);
        reader.close();

        GridSortMax solver = new GridSortMax();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.findMax(n, m, grid));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }
}
