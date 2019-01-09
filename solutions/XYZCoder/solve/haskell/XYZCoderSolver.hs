import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified XYZCoder (countWays)

getVars :: TC.Parser (Int, Int)
getVars = do room <- TC.spaces >> TC.parseInt ; TC.spaces >> TC.next
             size <- TC.spaces >> TC.parseInt
             return (room, size)

main = do
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (room, size) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ XYZCoder.countWays room size
            hClose hOut
    hClose hIn
