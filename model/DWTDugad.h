//
// Created by ilya on 08.11.16.
//

#ifndef WATERMARKENGINE_DWTDUGAD_H
#define WATERMARKENGINE_DWTDUGAD_H


#include <cmath>
#include "Watermark_Plugin.h"
#include "../utils/MyImage.h"
#include "Signature.h"

class DWTDugad: public Watermark_Plugin {
public:
    DWTDugad(){}
    virtual const char *
    embed(const char *msg_filename, const char *cover_filename, const char *stego_filename) override;

    virtual std::iostream & extract(const char *stego_filename, std::istream &orig_sig_data) override;

    void generate_signature(const char *passphrase, const char *file_name);

    virtual double get_watermark_correlation(std::istream &orig_sig_data, std::istream &watermark_data) override;

private:
    void wm_subBand(MyImage* img, double* wm, int n, double a,double threshold){
        for (int i = 0; i < img->getWidth() * img->getHeight(); ++i) {
            if (fabs(img->getData()[i]) > threshold){
                img->getData()[i] += (a * fabs(img->getData()[i]) * wm[i%n]);
            }
        }
    }

    double* inv_wm_subBand(MyImage* img, double* wm, int n, double threshold, double* val){

        std::fill_n(val, 3, 0.0);

        for(int i = 0; i < img->getWidth() * img->getHeight(); i++)
        {
            if(img->getData()[i] > threshold)
            {
                val[1] += (img->getData()[i] * wm[i % n]);
                val[2] += fabs(img->getData()[i]);
                val[0]++;
            }
        }

        return val;
    }
};


#endif //WATERMARKENGINE_DWTDUGAD_H