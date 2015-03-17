<?php

error_reporting(-1);
ini_set('display_errors', 'On');

if(isset($_POST['email']))
{
 
	// EDIT THE 2 LINES BELOW AS REQUIRED
	$email_to = "erich.viebrock@gmail.com";
	$email_subject = "Message from Portfolio";
	
    function died($error)
	{
		// your error code can go here
		echo "We are very sorry, but there were error(s) found with the form you submitted. ";
		echo "These errors appear below.<br /><br />";
		echo $error."<br /><br />";
		echo "Please go back and fix these errors.<br /><br />";
		die();
	}
 
    // validation expected data exists
	if(!isset($_POST['first_name']) ||
		!isset($_POST['last_name']) ||
		!isset($_POST['email']) ||
		!isset($_POST['telephone']) ||
		!isset($_POST['comments']))
	{
		died('We are sorry, but there appears to be a problem with the form you submitted.');
	}
 
    $first_name = $_POST['first_name']; // required
    $last_name = $_POST['last_name']; // required
    $email_from = $_POST['email']; // required
    $telephone = $_POST['telephone']; // not required
    $comments = $_POST['comments']; // required
	
    $error_message = "";
    $email_exp = '/^[A-Za-z0-9._%-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}$/';
 
	if(!preg_match($email_exp,$email_from))
	{
		$error_message .= 'The Email Address you entered does not appear to be valid.<br />';
	}
 
    $string_exp = "/^[A-Za-z .'-]+$/";
 
	if(!preg_match($string_exp,$first_name))
	{
		$error_message .= 'The First Name you entered does not appear to be valid.<br />';
	}
 
	if(!preg_match($string_exp,$last_name))
	{
		$error_message .= 'The Last Name you entered does not appear to be valid.<br />';
	}
 
	if(strlen($comments) < 2)
	{
		$error_message .= 'The Comments you entered do not appear to be valid.<br />';
	}
 
	if(strlen($error_message) > 0)
	{
		died($error_message);
	}
 
	$email_message = "Form details below:<br/><br/>";
	
	function clean_string($string)
	{
		$bad = array("content-type","bcc:","to:","cc:","href");
		return str_replace($bad,"",$string);
	}
 
	$email_message .= "&emsp;First Name: ".clean_string($first_name)."<br/>";
	$email_message .= "&emsp;Last Name: ".clean_string($last_name)."<br/>";
	$email_message .= "&emsp;Email: ".clean_string($email_from)."<br/>";
	$email_message .= "&emsp;Telephone: ".clean_string($telephone)."<br/>";
	$email_message .= "&emsp;Comments: ".clean_string($comments);
 
/*// create email headers
$headers = 'From: '.$email_from."\r\n".
'Reply-To: '.$email_from."\r\n" .
'X-Mailer: PHP/' . phpversion();*/

$headers = array("From: ".$email_from,
    "Reply-To: ".$email_from,
    "X-Mailer: PHP/" . PHP_VERSION
);
$headers = implode("\r\n", $headers);

$output = mail("evbrock20@hotmail.com", $email_subject, $email_message, $headers);
?>
 
<!-- include your own success html here -->
 
Thank you for reaching out! I will get back to you very soon.

<?php
}
?>