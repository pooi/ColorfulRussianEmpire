<h1 align=center>Colorful Russian Empire</h1>
<p align=center>흑백 사진 3장을 기반으로 컬러 사진을 만들어내는 프로그램입니다.</p>
<br>

>Contact & Help : ldaytw@gmail.com

## Introduce
It is a program that creates color photographs based on three black and white photographs taken in the same composition and it is the result of the school assignment.<br>
같은 구도에서 찍은 흑백 사진 3장을 기반으로 컬러 사진을 생성해내는 프로그램이며 학교 수업시간에 제출한 과제의 결과물입니다.
<br><br>

## Aim
This program aim to finish the calculation as quickly as possible.<br>
이 프로그램은 최대한 빠른 시간 내에 계산을 끝내는 것을 목표로 합니다.
<br><br>

## Usage
> You need opencv to use this program.<br>
> 이 프로그램을 사용하기 위해서는 opencv가 필요합니다.<br>
> <a href="http://www.opencv.org/releases.html">http://www.opencv.org/releases.html</a><br>
> 참고 : <a href="http://webnautes.tistory.com/716">http://webnautes.tistory.com/716</a>
```C
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

int main(){
  ...
  IplImage * src = cvLoadImage(fileName);
  ...
}
```
<br>

## Results
<table>
<tr>
<td width=20%><img src="https://github.com/pooi/ColorfulRussianEmpire/blob/master/result/001.jpg"> </td>
<td width=20%><img src="https://github.com/pooi/ColorfulRussianEmpire/blob/master/result/002.jpg"> </td>
<td width=20%><img src="https://github.com/pooi/ColorfulRussianEmpire/blob/master/result/003.jpg"> </td>
<td width=20%><img src="https://github.com/pooi/ColorfulRussianEmpire/blob/master/result/004.jpg"> </td>
<td width=20%><img src="https://github.com/pooi/ColorfulRussianEmpire/blob/master/result/005.jpg"> </td>
</tr>
<tr>
<td width=20%><img src="https://github.com/pooi/ColorfulRussianEmpire/blob/master/result/006.jpg"> </td>
<td width=20%><img src="https://github.com/pooi/ColorfulRussianEmpire/blob/master/result/007.jpg"> </td>
<td width=20%><img src="https://github.com/pooi/ColorfulRussianEmpire/blob/master/result/008.jpg"> </td>
<td width=20%><img src="https://github.com/pooi/ColorfulRussianEmpire/blob/master/result/009.jpg"> </td>
<td width=20%><img src="https://github.com/pooi/ColorfulRussianEmpire/blob/master/result/010.jpg"> </td>
</tr>
<tr>
<td width=20%><img src="https://github.com/pooi/ColorfulRussianEmpire/blob/master/result/011.jpg"> </td>
</tr>
</table>
<br>

## License
```
    Copyright 2016 Taewoo You

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
