import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified XMarksTheSpot (countArea)

getVars :: TC.Parser ([String])
getVars = do board <- TC.spaces >> (TC.parseList TC.parseString)
             return (board)

main = do
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (board) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ XMarksTheSpot.countArea board
            hClose hOut
    hClose hIn
