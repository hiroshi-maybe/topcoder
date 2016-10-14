import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified Xylophone (countKeys)

getVars :: TC.Parser ([Int])
getVars = do keys <- TC.spaces >> (TC.parseList TC.parseInt)
             return (keys)

main = do
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (keys) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ Xylophone.countKeys keys
            hClose hOut
    hClose hIn
