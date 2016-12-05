#!/usr/local/bin/perl
use strict;
use warnings;

my ($FILE,  @paraArr, $filetype, $operate);
my $query_string;
my $decode;
my $CONFIG_FILE = "//Library/WebServer/Documents/CONFIG";
my $CSZL_FILE = "/Library/WebServer/Documents/CSZL";
my $SBZL_FILE = "/Library/WebServer/Documents/SBZL";

my $referer = $ENV{'HTTP_REFERER'};
my $method = $ENV{'REQUEST_METHOD'};

sub URLDecode {
    my $theURL = $_[0];
    chomp($theURL);
    $theURL =~ tr/+/ /;
    $theURL =~ s/%([a-fA-F0-9]{2,2})/chr(hex($1))/eg;
    $theURL =~ s/<!--(.|\n)*-->//g;
    return $theURL;
}

sub getValueFromArray {
    my @Value = @_;
    my $want = $Value[0];
    shift(@Value);
    my $temp;
    foreach $temp (@Value) {
        if ($temp =~ /$want/) {
            $temp =~ s/$want=//;
            return $temp;
        }
    }
}

sub replaceNumInFile {
    my $name = $_[0];
    my $value = $_[1];
    my $filename = $_[2];
    my $line;
    open($FILE, "<", $filename);
    my @data = <$FILE>;
    close $FILE;
    open($FILE, ">", $filename);
    foreach $line (@data) {
        if ($line =~ $name) {
            $line =~ s/"$name": \d+/"$name": $value/;
        }
        print $FILE $line;
    }
    close $FILE;
}

sub replaceStrInFile {
    my $name = $_[0];
    my $value = $_[1];
    my $filename = $_[2];
    my $line;
    open($FILE, "<", $filename);
    my @data = <$FILE>;
    close $FILE;
    open($FILE, ">", $filename);
    foreach $line (@data) {
        if ($line =~ $name) {
            $line =~ s/"$name": ".*"/"$name": "$value"/;
        }
        print $FILE $line;
    }
    close $FILE;
}

sub existMacInFile {
    my $value = $_[0];
    my $filename = $_[1];
    my $line;
    open($FILE, "<", $filename);
    my @data = <$FILE>;
    close $FILE;
    foreach $line (@data) {
        if ($line =~ $value) {
            return 1;
        }
    }
    return 0;
}


if ($method =~ /GET/) {
    $query_string = $ENV{'QUERY_STRING'};
    die;
} else {
    $query_string = <STDIN>;
}

# 处理POST请求
$decode = URLDecode($query_string);
@paraArr = split(/&/, $decode);

$filetype = getValueFromArray("filetype", @paraArr);
$operate = getValueFromArray("operate", @paraArr);

if ($filetype =~ "CONFIG") {
    my $CONFIG_SWITCH = getValueFromArray("CONFIG_SWITCH", @paraArr);
    replaceNumInFile("SWITCH", $CONFIG_SWITCH, $CONFIG_FILE);
    my $CONFIG_SERVER = getValueFromArray("CONFIG_SERVER", @paraArr);
    replaceStrInFile("SERVER", $CONFIG_SERVER, $CONFIG_FILE);
    my $CONFIG_USERKEY = getValueFromArray("CONFIG_USERKEY", @paraArr);
    replaceStrInFile("USERKEY", $CONFIG_USERKEY, $CONFIG_FILE);
    my $CONFIG_DIR = getValueFromArray("CONFIG_DIR", @paraArr);
    replaceStrInFile("DIR", $CONFIG_DIR, $CONFIG_FILE);
    my $CONFIG_DataAcquisition = getValueFromArray("CONFIG_DataAcquisition", @paraArr);
    replaceStrInFile("DataAcquisition", $CONFIG_DataAcquisition, $CONFIG_FILE);
}

if ($filetype =~ "CSZL") {
    my $CSZL_SERVICE_CODE = getValueFromArray("CSZL_SERVICE_CODE", @paraArr);
    replaceStrInFile("SERVICE_CODE", $CSZL_SERVICE_CODE, $CSZL_FILE);
    my $CSZL_SERVICE_NAME = getValueFromArray("CSZL_SERVICE_NAME", @paraArr);
    replaceStrInFile("SERVICE_NAME", $CSZL_SERVICE_NAME, $CSZL_FILE);
    my $CSZL_ADDRESS = getValueFromArray("CSZL_ADDRESS", @paraArr);
    replaceStrInFile("ADDRESS", $CSZL_ADDRESS, $CSZL_FILE);
    my $CSZL_BUSINESS_NATURE = getValueFromArray("CSZL_BUSINESS_NATURE", @paraArr);
    replaceStrInFile("BUSINESS_NATURE", $CSZL_BUSINESS_NATURE, $CSZL_FILE);
    my $CSZL_SERVICE_TYPE = getValueFromArray("CSZL_SERVICE_TYPE", @paraArr);
    replaceNumInFile("SERVICE_TYPE", $CSZL_SERVICE_TYPE, $CSZL_FILE);
    my $CSZL_PROVINCE_CODE = getValueFromArray("CSZL_PROVINCE_CODE", @paraArr);
    replaceStrInFile("PROVINCE_CODE", $CSZL_PROVINCE_CODE, $CSZL_FILE);
    my $CSZL_CITY_CODE = getValueFromArray("CSZL_CITY_CODE", @paraArr);
    replaceStrInFile("CITY_CODE", $CSZL_CITY_CODE, $CSZL_FILE);
    my $CSZL_AREA_CODE = getValueFromArray("CSZL_AREA_CODE", @paraArr);
    replaceStrInFile("AREA_CODE", $CSZL_AREA_CODE, $CSZL_FILE);
    my $CSZL_XPOINT = getValueFromArray("CSZL_XPOINT", @paraArr);
    replaceStrInFile("XPOINT", $CSZL_XPOINT, $CSZL_FILE);
    my $CSZL_YPOINT = getValueFromArray("CSZL_YPOINT", @paraArr);
    replaceStrInFile("YPOINT", $CSZL_YPOINT, $CSZL_FILE);
    my $CSZL_TERMINAL_FACTORY_ORGCODE = getValueFromArray("CSZL_TERMINAL_FACTORY_ORGCODE", @paraArr);
    replaceStrInFile("TERMINAL_FACTORY_ORGCODE", $CSZL_TERMINAL_FACTORY_ORGCODE, $CSZL_FILE);
    my $CSZL_CREATE_TIME = getValueFromArray("CSZL_CREATE_TIME", @paraArr);
    replaceStrInFile("CREATE_TIME", $CSZL_CREATE_TIME, $CSZL_FILE);
}

sub insertInfoToSBZL {
    my @Value = @_;
    my $filename = $Value[0];
    shift(@Value);
    my @inputArr = @Value;
    open($FILE, "<", $filename);
    my @data = <$FILE>;
    close $FILE;

    open($FILE, ">", $filename);
    my $line;
    foreach $line (@data) {
        if ($line =~ /\[/) {
            print $FILE $line;
            print $FILE "    {\n";
            my $SBZL_EQUIPMENT_NUM = getValueFromArray("SBZL_EQUIPMENT_NUM", @inputArr);
            print $FILE "        \"EQUIPMENT_NUM\": \"$SBZL_EQUIPMENT_NUM\",\n";
            my $SBZL_EQUIPMENT_NAME = getValueFromArray("SBZL_EQUIPMENT_NAME", @inputArr);
            print $FILE "        \"EQUIPMENT_NAME\": \"$SBZL_EQUIPMENT_NAME\",\n";
            my $SBZL_MAC = getValueFromArray("SBZL_MAC", @inputArr);
            print $FILE "        \"MAC\": \"$SBZL_MAC\",\n";
            print $FILE "        \"IP\": \"\",\n";
            my $SBZL_SECURITY_FACTORY_ORGCODE = getValueFromArray("SBZL_SECURITY_FACTORY_ORGCODE", @inputArr);
            print $FILE "        \"SECURITY_FACTORY_ORGCODE\": \"$SBZL_SECURITY_FACTORY_ORGCODE\",\n";
            print $FILE "        \"VENDOR_NAME\": \"\",\n";
            print $FILE "        \"VENDOR_NUM\": \"\",\n";
            my $SBZL_SERVICE_CODE = getValueFromArray("SBZL_SERVICE_CODE", @inputArr);
            print $FILE "        \"SERVICE_CODE\": \"$SBZL_SERVICE_CODE\",\n";
            my $SBZL_PROVINCE_CODE = getValueFromArray("SBZL_PROVINCE_CODE", @inputArr);
            print $FILE "        \"PROVINCE_CODE\": \"$SBZL_PROVINCE_CODE\",\n";
            my $SBZL_CITY_CODE = getValueFromArray("SBZL_CITY_CODE", @inputArr);
            print $FILE "        \"CITY_CODE\": \"$SBZL_CITY_CODE\",\n";
            my $SBZL_AREA_CODE = getValueFromArray("SBZL_AREA_CODE", @inputArr);
            print $FILE "        \"AREA_CODE\": \"$SBZL_AREA_CODE\",\n";
            print $FILE "        \"INSTALL_DATE\": \"\",\n";
            print $FILE "        \"INSTALL_POINT\": \"\",\n";
            my $SBZL_EQUIPMENT_TYPE = getValueFromArray("SBZL_EQUIPMENT_TYPE", @inputArr);
            print $FILE "        \"EQUIPMENT_TYPE\": \"$SBZL_EQUIPMENT_TYPE\",\n";
            print $FILE "        \"LONGITUDE\": \"\",\n";
            print $FILE "        \"LATITUDE\": \"\",\n";
            print $FILE "        \"SUBWAY_STATION\": \"\",\n";
            print $FILE "        \"SUBWAY_LINE_INFO\": \"\",\n";
            print $FILE "        \"SUBWAY_VEHICLE_INFO\": \"\",\n";
            print $FILE "        \"SUBWAY_COMPARTMENT_NUM\": \"\",\n";
            print $FILE "        \"CAR_CODE\": \"\",\n";
            print $FILE "        \"UPLOAD_TIME_INTERVAL\": \"\",\n";
            print $FILE "        \"COLLECTION_RADIUS\": \"\",\n";
            my $SBZL_CREATE_TIME = getValueFromArray("SBZL_CREATE_TIME", @inputArr);
            print $FILE "        \"CREATE_TIME\": \"$SBZL_CREATE_TIME\",\n";
            print $FILE "        \"CREATER\": \"\",\n";
            print $FILE "        \"LAST_CONNECT_TIME\": \"\",\n";
            print $FILE "        \"REMARK\": \"\",\n";
            print $FILE "        \"WDA_VERSION\": \"\",\n";
            print $FILE "        \"FIRMWARE_VERSION\": \"\"\n";
            if ($#data > 10) {
                print $FILE "    },\n";
            } else {
                print $FILE "    }\n";
            }
        } else {
            print $FILE $line;
        }
    }
    close $FILE;
}

sub deleteInfoInSBZL {
    my @Value = @_;
    my $filename = $Value[0];
    shift(@Value);
    my @inputArr = @Value;
    open($FILE, "<", $filename);
    my $data = do { local $/; <$FILE> };
    close $FILE;
    my $MAC = getValueFromArray("SBZL_MAC", @inputArr);
    $data =~ s/(.*)(\s\s\s\s\s\{.*?$MAC.*?\},?)(.*)/$1$3/s;
    $data =~ s/(.*),(\n])/$1$2/s;
    open($FILE, ">", $filename);
    print $FILE $data;
    close $FILE;
}

# insert or modify SBZL
my $MAC = getValueFromArray("SBZL_MAC", @paraArr);
if (($filetype =~ /SBZL/) && ($operate =~ /modify/)) {
    if (!existMacInFile($MAC, $SBZL_FILE)) {
        insertInfoToSBZL($SBZL_FILE, @paraArr);
    } else {
        deleteInfoInSBZL($SBZL_FILE, @paraArr);
        insertInfoToSBZL($SBZL_FILE, @paraArr);
    }
}

if (($filetype =~ /SBZL/) && ($operate =~ /delete/)) {
    if (existMacInFile($MAC, $SBZL_FILE)) {
        deleteInfoInSBZL($SBZL_FILE, @paraArr);
    }
}

print "Location: $referer\n\n";
