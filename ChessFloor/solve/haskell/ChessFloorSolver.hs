import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified ChessFloor (minimumChanges)

getVars :: TC.Parser ([String])
getVars = do floor <- TC.spaces >> (TC.parseList TC.parseString)
             return (floor) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (floor) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ ChessFloor.minimumChanges floor
            hClose hOut
    hClose hIn