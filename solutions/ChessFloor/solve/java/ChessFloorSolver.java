import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class ChessFloorSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        List<String> floorBoxed = (List<String>) reader.next(new TypeRef<List<String>>(){}.getType());
        String[] floor = new String[floorBoxed.size()];
        for (int _i = 0; _i < floorBoxed.size(); ++_i)
            floor[_i] = floorBoxed.get(_i);
        reader.close();

        ChessFloor solver = new ChessFloor();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.minimumChanges(floor));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
