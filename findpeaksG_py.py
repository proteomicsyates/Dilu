import numpy as np
import sys
from numpy import Inf, arange, isscalar, asarray, array

def peakdet(v, delta, x=None):
    maxtab = []
    if x is None:
        x = arange(len(v))
    v = asarray(v)
    if len(v) != len(x):
        sys.exit('Input vectors v and x must have same length')
    if not isscalar(delta):
        sys.exit('Input argument delta must be a scalar')
    if delta <= 0:
        sys.exit('Input argument delta must be positive')
    mn, mx = Inf, -Inf
    lookformax = True
    lasti = 0
    for i in arange(len(v)):
        this = v[i]
        if this > mx:
            mx = this
            lasti = i
        if this < mn:
            mn = this
        if lookformax:
            if this < mx - delta:
                maxtab.append(lasti)
                mn = this
                lasti = i
                lookformax = False
        else:
            if this > mn + delta:
                mx = this

                lookformax = True

    return array(maxtab)


def gaussfit(x,y):
    maxy=np.max(y)
    y=np.clip(y,maxy/100,maxy)
    z=np.log(y)
    coef=np.polyfit(x,z,2)
    a=coef[2]
    b=coef[1]
    c=coef[0]
    Height=np.exp(a - c * (b / (2 * c)) ** 2)
    Position=-b/(2*c)
    Width=2.35482/(1.414*np.sqrt(np.abs(c)))
    return Height,Position,Width

def findpeaksG(x, y, slope=0, Amp=0, smooth_width=50, peakgroup=50, smoothtype=1):
    y_deriv = np.gradient(np.array(y, dtype=np.float))
    d = fast_smooth(y_deriv,smooth_width,1)
    n = np.round(peakgroup / 2 + 1).astype(int)
    vectorlength = len(y)
    for j  in range(2 * np.round(smooth_width / 2) - 1,len(y) - smooth_width - 1):
        if np.sign(d[j]) > np.sign(d[j + 1]):
            if y[j]>Amp or y[j+1]>Amp:
                xx=np.zeros(peakgroup)
                yy=xx

def fast_smooth(data_1d, s_width, s_type):  # derivative of y, smooth width, smooth type 1.rectangular, 2. triangular, 3.psudo-gaussian
    if s_type == 1:
        y = np.convolve(data_1d, np.ones((s_width,)) / s_width, mode='valid')
        sss = (s_width - 1) / 2.0
        head = np.floor(sss).astype(int)
        tail = np.ceil(sss).astype(int)
        return np.insert(np.insert(y, y.size, np.zeros(tail)), 0, np.zeros(head))
    else:
        return 0

def fit_gauss(file_in, file_out):
    with open(file_out,'wb') as output:
        binary_data=np.fromfile(file_in,dtype='d')
        i=0
        while i<len(binary_data):
            mass = round(binary_data[i]*10000)/10000.0
            number_of_point = int(binary_data[i + 1])
            log_intensity = binary_data[i + 2]
            x = binary_data[i + 3:i + number_of_point + 3]
            y = binary_data[i + number_of_point + 3:i + number_of_point * 2 + 3]
            score=np.percentile(y,97)/np.mean(y)
            delta = 1 * np.median(y)
            amp = 0.05 * np.max(y)
            delta = amp if amp > delta else delta
            peak_list = peakdet(y, delta, x)
            output.write('#\n')
            output.write(str(score)+'\n')
            output.write(str(mass)+'\n')
            for each_peak in peak_list:
                if each_peak>30:
                    fitlist=gaussfit(x[each_peak - 25:each_peak + 25], y[each_peak - 25:each_peak + 25])
                    output.write(','.join(format(x, ".4f") for x in fitlist)+'\n')
            incre=3+number_of_point*2
            i+=incre
    open('done.res', 'a').close()
    return 0

if __name__=='__main__':
    if len(sys.argv)<3:
        sys.exit("usage: findpeaksG_py [input file, in dilu format] [output file, in txt]")
    else:
        fit_gauss(sys.argv[1],sys.argv[2])
        open('done.res', 'a').close()
