function show_info{
    param(
        [string]$info
    )
    Write-Host $info
}


function read_links {
    param (
        [string] $cproject_path
    )
    if(Test-path $cproject_path){
        $data = Get-Content $cproject_path
        $data_link = @()
        $find_flag = $false
        $index_offset = 0
        for($i = 0; $i -lt $data.Count; $i++){       
                if($data[$i] -match "<linkedResources>"){
                    $find_flag = $true
                    $index_offset = $i
                }
                if($find_flag){
                    $data_link += $data[$i]
                }          
                if($data[$i] -match "</linkedResources>"){
                    break
                }            
        }

        [System.Collections.ArrayList]$stack_temp = @()
        [System.Collections.ArrayList]$position_cconfiguration = @()
        [System.Collections.ArrayList]$position_temp = @()
        for($i = 0; $i -lt $data_link.Count; $i++){
            $results = [regex]::Matches($data_link[$i], "<[a-zA-Z0-9]{1,}")
            if($results.Count -gt 0){
                for($j = 0; $j -lt $results.Count; $j++){
                    if($results[$j].Value -eq "<link"){
                        $position_temp += $i + $index_offset
                        $stack_temp = @()
                        $stack_temp += $results[$j].Value
                        for($k = $j+1; $k -lt $results.Count; $k++)
                        {
                            $stack_temp += $results[$k].Value
                        }
                    }
                    else {
                        $stack_temp += $results[$j].Value
                    }
                }
            }

            $results = [regex]::Matches($data_link[$i], "<?/[a-zA-Z]{0,}>")
            if($results.Count -gt 0){
                for($j = 0; $j -lt $results.Count; $j++){
                    if(($stack_temp.Count -eq 1) -and ($position_temp.Count -eq 1)){
                        $position_temp += $i + $index_offset
                        $name = ""
                        $find_flag = $false
                        for($k = $position_temp[0]; $k -le $position_temp[1]; $k++){
                            if($data[$k] -match "<name>"){
                                $find_flag = $true
                            }   
                            if($find_flag){
                                $name += $data[$k]
                            }
                            if($data[$k] -match "</name>"){
                                break
                            }                      
                        }
                        $name = $name -replace "<name>", "" -replace "</name>", "" -replace " ", "" -replace "\t", ""
                        $position_temp += $name
                            
                        $position_cconfiguration += (, $position_temp)
                        $position_temp = @()
                    }
                    elseif ($stack_temp.Count -gt 0) {
                        $stack_temp.RemoveAt($stack_temp.Count-1)
                    }
                }
            }

        }
        return $position_cconfiguration

    }
    else{
        show_info "File '.project' does not exist."
        return @()
    }
}

function read_options {
    param (
        [string] $cproject_path
    )
    if(Test-path $cproject_path){
        $data = Get-Content $cproject_path
        # show_info $data
        [System.Collections.ArrayList]$stack_temp = @()
        [System.Collections.ArrayList]$position_cconfiguration = @()
        [System.Collections.ArrayList]$position_temp = @()
        for($i = 0; $i -lt $data.Count; $i++){
            $results = [regex]::Matches($data[$i], "<[a-zA-Z0-9]{1,}")
            if($results.Count -gt 0){
                for($j = 0; $j -lt $results.Count; $j++){
                    if($results[$j].Value -eq '<cconfiguration'){
                        $position_temp += $i
                        $stack_temp = @()
                        $stack_temp += $results[$j].Value
                        if($j -ne $results.Count){
                            for($k = $j+1; $k -lt $results.Count; $k++){
                                $stack_temp += $results[$k].Value
                            }
                        }
                        break
                    }
                    else{
                        $stack_temp += $results[$j].Value
                    }
                }
            }
            $results = [regex]::Matches($data[$i], "<?/[a-zA-Z]{0,}>")
            if($results.Count -gt 0){
                # show_info $results[0].Value
                for($j = 0; $j -lt $results.Count; $j++){
                    if(($stack_temp.Count -eq 1) -and ($position_temp.Count -eq 1)){
                        $position_temp += $i
                        $name = '' 
                        for($k = $position_temp[0]; $k -lt $position_temp[1]; $k++){
                            if($data[$k] -match '<storageModule'){
                                $result_temp = [regex]::Matches($data[$k], 'name="[0-9a-zA-Z_]{1,}"')
                                if($result_temp.Count -gt 0){
                                    $name = $result_temp[0].Value.Substring(6, $result_temp[0].Value.Length-7)
                                    # show_info $name
                                    break
                                }
                            }                        
                        }
                        $position_temp += $name
                        $position_cconfiguration += (,$position_temp)
                        $position_temp = @()
                        break
                    }
                    elseif ($stack_temp.Count -gt 0){
                        # show_info $position_temp
                        # show_info $stack_temp
                        $stack_temp.RemoveAt($stack_temp.Count-1)
                    }
                }
            }

        }
        return $position_cconfiguration
    }
    else{
        show_info "File '.cproject' does not exist."
        return @()
    }
}

# function remove_option {
#     param (
#         [string] $cproject_path,
#         [string] $option
#     )
#     $position_cconfiguration = read_options($cproject_path)
#     if($position_cconfiguration.Count -gt 0){
#         $begin = 0
#         $end = $begin
#         foreach ($cconfiguration in $position_cconfiguration){
#             # show_info $cconfiguration
#             if($cconfiguration[2] -eq $option){
#                 $begin = $cconfiguration[0]
#                 $end = $cconfiguration[1]
#                 show_info ("Remove complie option: " + $option)
#                 break
#             }
#         } 
#         $data_temp = @()
#         $data = Get-Content $cproject_path
#         if ($begin -ne $end){
#             for($i = 0; $i -lt $data.Count; $i++){
#                 if(($i -lt $begin) -or ($i -gt $end)){
#                     # show_info $data[$i]
#                     $data_temp += $data[$i]
#                 }
#             }
#         }
#         # show_info $data_temp
#         if($data_temp.Count -gt 0){
#             Set-Content $cproject_path $data_temp
#         }
#     } 
# }
function remove_links {
    param (
        [string] $project_path,
        [string] $value
    )
    [System.Collections.ArrayList]$scale_save = @()
    [System.Collections.ArrayList]$position_temp = @()
    $position_cconfiguration = read_links($project_path)
    $values = $value.Split(',')
    for($i = 0; $i -lt $values.Count; $i++){
        foreach ($cconfiguration in $position_cconfiguration){
            $values[$i] = $values[$i] -replace " ", "" -replace "\t", "" -replace "\\", "/"
            if($values[$i] -eq $cconfiguration[2]){
                $position_temp = @()
                $position_temp += $cconfiguration[0]
                $position_temp += $cconfiguration[1]
                $scale_save += (,$position_temp)
                show_info ("Remove file link: " + $values[$i])
            }
        }
    }

    $data = Get-Content $project_path
    $data_temp = @()

    for($i = 0; $i -lt $data.Count; $i++)
    {
        $save_flag = $true
        foreach($scale in $scale_save){
            if($i -ge $scale[0] -and $i -le $scale[1]){
                $save_flag = $false
                break
            }
        }
        if($save_flag){
            $data_temp += $data[$i]
        }
    }

    if($data_temp.Count -gt 0){
        Remove-Item -Path $project_path -Recurse -Force
        Set-Content $project_path $data_temp
    }
}


function remove_options {
    param (
        [string] $cproject_path,
        [string] $value
    )
    [System.Collections.ArrayList]$scale_save = @()
    [System.Collections.ArrayList]$position_temp = @()
    $position_cconfiguration = read_options($cproject_path)
    $values = $value.Split(',')
    for($i = 0; $i -lt $values.Count; $i++){
        foreach ($cconfiguration in $position_cconfiguration){
            if($values[$i] -eq $cconfiguration[2]){
                $position_temp = @()
                $position_temp += $cconfiguration[0]
                $position_temp += $cconfiguration[1]
                $scale_save += (,$position_temp)
                show_info ("Remove complie option: " + $values[$i])
            }
        }
    }

    $data = Get-Content $cproject_path
    $data_temp = @()

    for($i = 0; $i -lt $data.Count; $i++)
    {
        $save_flag = $true
        foreach($scale in $scale_save){
            if($i -ge $scale[0] -and $i -le $scale[1]){
                $save_flag = $false
                break
            }
        }
        if($save_flag){
            $data_temp += $data[$i]
        }
    }

    if($data_temp.Count -gt 0){
        Remove-Item -Path $cproject_path -Recurse -Force
        Set-Content $cproject_path $data_temp
    }
}

function read_config{
    param (
        [string]$cfg_path,
        [string]$section,
        [string]$key
    )
    if(Test-path $cfg_path){
        $data = Get-Content $cfg_path
        $flag = $false
        $section_content = ''
        for($i = 0; $i -lt $data.count; $i++){
            if($data[$i] -match "\[$section\]"){
                $flag = $true
                continue
            }
            elseif($data[$i] -match "\[[a-zA-Z0-9]{1,}\]"){
                $flag = $false
            }
            if($flag){
                $section_content += $data[$i] + '$'
            }
        }
        $lines = $section_content.Split('$')
        $value = ''
        for($i = 0 ; $i -lt $lines.Count; $i++){
            $key_value = $lines[$i].Split('=')

            if(($key_value.Count -ge 2) -and ($key_value[0] -match $key)){            
                $value = $key_value[1]
                for($j = 2; $j -lt $key_value.Count; $j++){
                    $value += "=" + $key_value[$j]
                }
                while($value -and ($value[0] -eq " ")){
                    $value = $value.Substring(1, $value.Length-1)
                }
                break
            }
        }
        # show_info $value
        return $value
    }
    else{
        show_info "The configuration file does not exist."
        return ''
    }
}

function remove_files{
    param (
        [string]$project_path,
        [string]$value
    )
    # show_info $value
    $rm_path = $project_path
    $values = $value.Split(',')
    for($i = 0; $i -lt $values.Count; $i++){
        $rm_temp = $values[$i]
        # show_info $rm_temp
        if($rm_temp.EndsWith('\')){
            $rm_path = $project_path + $rm_temp
            # show_info $rm_path
        }
        else{
            $rm_file_dir = $rm_path + $rm_temp
            # show_info $rm_file_dir
            if(Test-Path $rm_file_dir){
                Remove-Item -Path $rm_file_dir -Recurse -Force
                show_info ('Remove ' + $rm_file_dir)
            }
        }
    }
}

function remove_headers{
    param (
        [string]$path,
        [string]$value
    )
    if(Test-Path $path){
        $values = $value.Split(',')
        $data = Get-Content $path
        $data_temp = @()
        for($i = 0; $i -lt $data.Count; $i++)
        {
            $flag = $true
            for($j = 0; $j -lt $values.Count; $j++){
                if($values[$j].EndsWith('.h')){
					$tmpValues = $values[$j].Split('\')
                    if($data[$i] -match $tmpValues[$tmpValues.Count-1]){
                        $flag = $false
                        break
                    }
                }
            }
            if($flag){
                $data_temp += $data[$i]
            }
        }
        Set-Content $path $data_temp
    }
}

function set_macro{
    param (
        [string]$path,
        [string]$key,
        [string]$value
    )
	$pattern = "#define[ `t]{1,}"+$key
    $key = '#define ' + $key
    if(Test-Path $path){
        $data = Get-Content $path
        $data_temp = @()
        for($i = 0; $i -lt $data.Count; $i++){
            if($data[$i] -match $pattern){
                $data_temp += ($key + "`t`t" + $value)
                show_info ("set macro " + $key + " to " + $value + " in " + $path + " successfully.")
            }
            else{
                $data_temp += $data[$i]
            }
        }
		
		Remove-Item -Path $path -Recurse -Force
        Set-Content $path $data_temp		
    }
    else{
        show_info ($path + " do not exist")
    }
}

function show_help {
    show_info "usage:       [command] [para1][...]"
    show_info "command:     rm_options, rm_files, rd_options, rd_config, help"
    show_info "rm_options:  para[1] project path,               para[2] configuration file path,"
    show_info "             para[3] configuration section,      para[4] path of file .cproject."
    show_info "rm_links:    para[1] project path,               para[2] configuration file path,"
    show_info "             para[3] configuration section,      para[4] path of file .project."
    show_info "rm_files:    para[1] project path,               para[2] configuration file path,"
    show_info "             para[3] configuration section,      argv[4] file to remove include header"
    show_info "rd_options:  para[1] project path,               para[2] path of file .cproject,"
    show_info "             para[3] path to save read options."
    show_info "rd_config:   para[1] configuration file path,    para[2] configuration section,"
    show_info "             para[3] configuration key,          para[4] path to save read configures."
    show_info "st_macro:    para[1] file path,                  para[2] macro name,"
    show_info "             para[3] value to set."
    show_info "st_node:     para[1] .cproject file path,        para[2] config file path,"
    show_info "             para[3] section_name,               para[3] format string, split by ':'"
    show_info "help:        None."
}

function main{
param(
    [string]$argv0,
    [string]$argv1,
    [string]$argv2,
    [string]$argv3,
    [string]$argv4
)
$cmd = $argv0
switch($cmd){
    rm_options{
        if([string]::IsNullOrEmpty($argv4)){
            show_info "Incomplete parameters."
        }
        else{
            # show_info $argv0
            # show_info $argv1
            # show_info $argv2
            # show_info $argv3
            # show_info $argv4
            $project_path = $argv1
            if($project_path.EndsWith('\') -eq $false){
                $project_path += '\'
            }
            $config_path = $argv2
            $config_section = $argv3
            $cproject_path = $project_path + $argv4
            show_info $cproject_path
            $value = read_config $config_path $config_section "rm_options"
            if($value.Length -gt 0){
            #     $values = $value.Split(',')
                # for($i = 0; $i -lt $values.Count; $i++){
                #     # show_info $values[$i]
                #     remove_option $cproject_path $values[$i]
                # }
                remove_options $cproject_path $value
            }    
        }
    }
    rm_links{
        if([string]::IsNullOrEmpty($argv4)){
            show_info "Incomplete parameters."
        }
        else{
            $project_path = $argv1
            if($project_path.EndsWith('\') -eq $false){
                $project_path += '\'
            }
            $config_path = $argv2
            $config_section = $argv3
            $project_path = $project_path + $argv4
            show_info $project_path
            $value = read_config $config_path $config_section "rm_links"
            if($value.Length -gt 0){
                remove_links $project_path $value
            }    
        }
    }
    rm_files{
        if([string]::IsNullOrEmpty($argv4)){
            # show_info $argv0
            # show_info $argv1
            # show_info $argv2
            # show_info $argv3
            if([string]::IsNullOrEmpty($argv3))
            {
                show_info "Incomplete parameters."
            }
            else{
                $project_path = $argv1    
                if($project_path.EndsWith('\') -eq $false){
                    $project_path += '\'
                }
                $config_path = $argv2
                $config_section = $argv3
                $value = read_config $config_path $config_section 'rm_files'
                # show_info $value
                if($value.Length -gt 0){
                    remove_files $project_path $value
                }
            }
        }
        else {
            $project_path = $argv1
            if($project_path.EndsWith('\') -eq $false){
                $project_path += '\'
            }
            $config_path = $argv2
            $config_section = $argv3
            $header_file_path = $project_path + $argv4
            $value = read_config $config_path $config_section 'rm_files'
            # show_info $value
            # show_info $header_file_path
            if($value.Length -gt 0){
                remove_headers $header_file_path $value
            }
        }
    }
    rd_options{
        if([string]::IsNullOrEmpty($argv3)){
            show_info "Incomplete parameters."
        }
        else{
            # show_info $argv0
            # show_info $argv1
            # show_info $argv2
            # show_info $argv3
            $project_path = $argv1
            if($project_path.EndsWith('\') -eq $false){
                $project_path += '\'
            }
            $cproject_path = $project_path + $argv2
            $path_save = $argv3
            # show_info $cproject_path
            # show_info $path_save
            $position_cconfiguration = read_options($cproject_path)
            if($position_cconfiguration.Count -gt 0){
                $data_temp = @()
                for($i = 0; $i -lt $position_cconfiguration.Count; $i++){
                    # show_info $position_cconfiguration[$i][2]
                    $data_temp += $position_cconfiguration[$i][2]
                }
                Set-Content $path_save $data_temp
            }
        }
    }
    rd_config{
        if([string]::IsNullOrEmpty($argv4)){
            show_info "Incomplete parameters."
        }
        else{
            $config_path = $argv1
            $config_section = $argv2
            $config_key = $argv3
            $path_save = $argv4
            $value = read_config $config_path $config_section $config_key
            # show_info $value
            if($value.Length -gt 0){
                $values = $value.Split(',')
                $data_temp = @()
                for($i = 0; $i -lt $values.count; $i++){
                    $data_temp += $values[$i]
                }
                Set-Content $path_save $data_temp
            }
        }
    }
    st_macro{
        if([string]::IsNullOrEmpty($argv3)){
            show_info "Incomplete parameters."
        }
        else{
            $file_path = $argv1
            $macro = $argv2
            $value = $argv3
            set_macro $file_path $macro $value
        }
    }
    st_node{
        if([string]::IsNullOrEmpty($argv4)){
            show_info "Incomplete parameters."
        }
        else{
            $file_path = $argv1
            $cfg_path = $argv2
            $section_name = $argv3
            $format_info = $argv4
            $format_list = $format_info.Split(':')
    
            $node_path = read_config $cfg_path $section_name "node_path"
            if(!$node_path){
                show_info $cfg_path"->"$section_name"->node_path error."
            }
            $node_value = read_config $cfg_path $section_name "node_value"
            if(!$node_value){
                show_info $cfg_path"->"$section_name"->node_value error."
            }
            # $node_path
            # $node_value

            $node_temp = $node_path + "@"+ $node_value
            try {
                $node_temp = $node_temp -f $format_list
            }
            catch {
                show_info "String Format Error."
                break
            }

            $node_temp_list = $node_temp.Split("@")

            if($node_temp_list.Count -ne 2){
                show_info "String in node_path/node_value could not be '@' "
            }

            $node_path = $node_temp_list[0]
            $node_value = $node_temp_list[1]

            set_node $file_path $node_path $node_value
            
        }
    }
    help{
        show_help
    }
    default{
        show_info "[command] error!"
        show_help
    }
}
}

function compare_list{
    param(
        [array]$path_list,
        [array]$read_list
    )
    # $path_list.Count
    # $read_list.Count
    if($path_list.Count -ne $read_list.Count){
        return $false
    }

    $rtn_bool = $true

    for($i = 0; $i -lt $path_list.Count; $i++){
        foreach($item in $path_list[$i].Keys){
            # show_info "================="
            # $path_list[$i].$item
            # $read_list[$i].$item
            # show_info "================="
            if($path_list[$i].$item -ne $read_list[$i].$item){
                $rtn_bool = $false
                break
            }
        }
    }

    return $rtn_bool
}
function string2list{
    param(
        [string]$info
    )
    $info_list = $info.Split(":")
    if($info_list.Count -eq 0){
        return @()
    }
    else {
        $rtn_list = @()
        for($i = 0; $i -lt $info_list.Count; $i++)
        { 
            if(!$info_list[$i]){
                continue
            }  
            $temp_info = "<" + $info_list[$i] + ">"
            $rtn_list += string2hash($temp_info)      
        }
        return $rtn_list
    }
}
function string2hash{
    param (
        [string]$info
    )
    $results = [regex]::Matches($info, "<[a-zA-Z0-9]{1,}( [^>]{1,}){0,}>")
    if($results.Count -le 0){
        return @{}
    }
    else {
        $rtn_hash = @{}
        $info = $info.Substring(1, $info.Length-2)
        if($info[$info.Length-1] -eq "/"){
            $info = $info.Substring(0, $info.Length-1)
        }
        $info_list = $info.Split(" ")
        $rtn_hash.Add("path", $info_list[0])

        for($i = 1; $i -lt $info_list.Count; $i++){
            $value = ""
            $key_value = $info_list[$i].Split("=")
            if($key_value.Count -lt 2){
                continue
            }elseif($key_value.Count -eq 2){
                $value += $key_value[1]
            }else{
                $value += $key_value[1]
                for($j = 2; $j -lt $key_value.Count; $j++){
                    $value += "=" + $key_value[$j]
                }
            }
     
            for($j = $i+1; $j -lt $info_list.Count; $j++)
            {
                if(!($info_list[$j] -match "=")){
                    $value += " "+$info_list[$j]
                }
                else {
                    break
                }
            }

            $rtn_hash.Add($key_value[0], $value)
        }

        return $rtn_hash
    }
}
function set_node{
    param (
        [string]$cproject_path,
        [string]$node_path,
        [string]$node_value
    )
    if(Test-path $cproject_path){
        $node = string2list($node_path)
        if(!$node){
            return
        }

        $data = Get-Content $cproject_path
        # show_info $data
        [System.Collections.ArrayList]$stack_temp = @()
        $data_temp = @()
        $exec_flag = $false
        for($i = 0; $i -lt $data.Count; $i++){
            $line_temp = $data[$i]
            $match_flag = $flase
            if(!$exec_flag){
                $results = [regex]::Matches($line_temp, "<[a-zA-Z0-9]{1,}(( [^>]{1,}){0,}|[/])>")
                if($results.Count -gt 0){
                    for($j = 0; $j -lt $results.Count; $j++){
                        # $results[$j].value
                        $hash = string2hash($results[$j].value)
                        $stack_temp += $hash 
                        # if($i -gt 48) {
                        #     show_info "---------------------------------"
                        #     $stack_temp[9]
                        #     show_info "---------------------------------"
                        #     $node[9]
                        #     compare_list $node $stack_temp 
                        #     show_info "-----------"
                        #     $node.Count
                        #     return
                        # }   
                        $match_flag = compare_list $node $stack_temp
                    }
                }
                $results = [regex]::Matches($line_temp, "<?/[a-zA-Z]{0,}>")
                if($results.Count -gt 0){
                    for($j = 0; $j -lt $results.Count; $j++){
                        # $results[$j].value
                        if($stack_temp.Count -gt 0){
                            $stack_temp.RemoveAt($stack_temp.Count-1)
                        }
                    }
                }
            }

            if($match_flag ){
                # $i
                # $line_temp
                $temp = [array]($node[$node.Count-1].Keys)
                if($temp.Count -ge 1){
                    $key_temp = $temp[0]
                    $value_temp = $key_temp + "=" + $node[$node.Count-1].$key_temp
                    if($line_temp -match $value_temp){
                        $line_temp = $line_temp.Replace($value_temp, $node_value)
                        $exec_flag = $true
                        show_info ("Replace " + $value_temp + " to " + $node_value + " successfully.")
                    }
                }      
            }
            $data_temp += $line_temp
        }

        Remove-Item -Path $cproject_path -Recurse -Force
        Set-Content $cproject_path $data_temp

        if(!$exec_flag){
            show_info ("Replace noting to " + $node_value + ", it may be target value.")
        }
    }
    else{
        show_info "File '.cproject' does not exist."
        return ""
    }
}

main $args[0] $args[1] $args[2] $args[3] $args[4]
# read_config .\test_cfg.ini hello2 hello2
# remove_option .\.cproject B91_UART_Demo
# remove_files .\ 'test\,test1,test2.txt'
# remove_headers .\test\driver_b91.h 'dma.h,watchdog.h'
# read_links D:\xupengcheng_workspace\2022\0304_Release_Tool\prj\telink_b85m_driver_src\project\tlsr_tc32\B85\.project
# remove_links D:\xupengcheng_workspace\2022\0304_Release_Tool\prj\telink_b85m_driver_src\project\tlsr_tc32\B85\.\.project "boot, vendor/Test_Demo"
#set_macro D:\xupengcheng_workspace\2022\0323_otp_protection_code\prj\telink_b85m_driver_src\tools\release_sdk_tool\tool\test\pm.c OTP_PROTECTION_CODE_SELECT OTP_PROTECTION_CODE_S0
#set_node '.\.cproject' '<cproject>/<storageModule>/<cconfiguration>/<storageModule>/<configuration name="UART_Demo">/<folderInfo>/<toolChain>/<tool>/<option>/<listOptionValue value="MCU_STARTUP_FLASH=1">' 'value="MCU_STARTUP_RAM=1"'
#set_node '.\.cproject' '<cproject>/<storageModule>/<cconfiguration>/<storageModule>/<configuration name="UART_Demo">/<folderInfo>/<toolChain>/<tool>/<option value="../link/flash_boot.link">' 'value="../link/ram_boot.link"'
#main st_node '.\.cproject' "..\config\config.ini::B91_SRAM_Macro"