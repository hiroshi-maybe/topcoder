import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified ABBA (canObtain)

getVars :: TC.Parser (String, String)
getVars = do initial <- TC.spaces >> TC.parseString ; TC.spaces >> TC.next
             target <- TC.spaces >> TC.parseString
             return (initial, target) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (initial, target) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ ABBA.canObtain initial target
            hClose hOut
    hClose hIn