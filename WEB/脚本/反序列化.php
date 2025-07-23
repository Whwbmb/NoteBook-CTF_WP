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


// class Flag{  
//     public $file;  
//     public function __construct(){  
//         $this->file = "flag.php";  
//     }
// }
// $file=new Flag();
// $flag=serialize($file);
// $flag1=urlencode($flag);
// echo $flag1;
// ?>  


<?php  
$b1="MAUXXQC";
$b2="MMHUWUV";
// if($b1!=$b2&&md5($b1)==md5($b2)){
if($b1!=$b2&&md5($b1)===md5($b2)){
    
    echo "true\n";
    echo "flag{".md5($b1)."}\n";
    echo "flag{".md5($b2)."}";

}else{
    echo "false\n";
    echo "flag{".md5($b1)."}\n";
    echo "flag{".md5($b2)."}";
}
?>  