//
//  const char * documentsFolder(void);  Utilities.m
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/13/19.
//

#import <Foundation/Foundation.h>

#import "Utilities.h"

const char * documentsFolder(void)
{
    NSArray*    documentDir = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString*    path = nil;
    
    if (documentDir)
    {
        path = [documentDir objectAtIndex:0];
    }
    
    return [path fileSystemRepresentation];
}

const char * resoursesFolder(void)
{
    NSString*    path = [[NSBundle mainBundle] resourcePath];
    return [path fileSystemRepresentation];
}
